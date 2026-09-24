#include <cassert>
#include <cstdio>
#include <cstdint>
#include <string>
#include <algorithm>
#include "MusicRecovery.h"
using std::string;
using uint32 = uint32_t;
using int32 = int32_t;
using AudioHandle = uintptr_t;
#define AUDIO_HANDLE_BLANK 0
struct Globals { string m_lastMusicPath, m_dmodGameDir, m_dmodGamePathWithDir;
    string m_gamePathWithDir = "dink/"; } g_dglo;
struct Audio {
    bool available = false;
    AudioHandle handle = 0;
    AudioHandle Play(const string&, bool, bool, bool) { return handle = available ? 7 : 0; }
    AudioHandle GetLastMusicID() { return handle; }
    bool IsPlaying(AudioHandle id) { return id != 0; }
    uint32 GetPos(AudioHandle id) { assert(id != 0); return 1234; }
    void StopMusic() { handle = 0; }
    void SetMusicVol(float) {}
    void SetPos(AudioHandle id, uint32) { assert(id != 0); }
} audio;
Audio* GetAudioManager() { return &audio; }
int* pmap = nullptr;
struct MapInfo { int music[769] = {}; } g_MapInfo;
struct StaticGlobals { bool midi_active=true, m_hasMusicModApplied=false; float m_musicModVolume=1; } g_dglos;
struct Var { float GetFloat() { return 1; } } var;
struct App { Var* GetVar(const char*) { return &var; } } app;
App* GetApp() { return &app; }
string GetSavePath() { return "./"; }
void playbank(int, int, int, int, int, int) {}

string ToLowerCaseString(string s) { for (char& c : s) c = std::tolower(c); return s; }
void StringReplace(const string& a, const string& b, string& s) {
    size_t p = 0; while ((p = s.find(a, p)) != string::npos) { s.replace(p, a.size(), b); p += b.size(); }
}
string GetFileExtension(const string& s) { return s.substr(s.rfind('.')+1); }
string ModifyFileExtension(const string& s, const string& ext) { return s.substr(0, s.rfind('.')+1)+ext; }
bool FileExists(const string& s) { return GetFileExtension(s) == "mid"; }
string GetFileLocationString(const string& s) { return "dink/"+s; }
void LogError(const char*, ...) {}
namespace dink_music_diagnostics { void write(const char*, ...) {} }
struct soundstruct { int repeat=0, owner=0, survive=0, vol=0, freq=0; } soundinfo[1];
struct SoundInfo { string m_fileName; } g_soundInfo[1];
struct SoundBank { bool IsInUse() { return false; } int m_soundIDThatPlayedUs=0; } soundbank[1];
int num_soundbanks=0, max_sounds=0;
void SaveToFile(const string& s, FILE* f) {
    uint32 len=static_cast<uint32>(s.size()); fwrite(&len, 4, 1, f); fwrite(s.data(), 1, len, f);
}
template<class T> void SaveToFile(T v, FILE* f) { fwrite(&v, sizeof(v), 1, f); }
void LoadFromFile(string& s, FILE* f) {
    uint32 len; assert(fread(&len,4,1,f)==1); s.resize(len); assert(fread(&s[0],1,len,f)==len);
}
template<class T> void LoadFromFile(T& v, FILE* f) { assert(fread(&v,sizeof(v),1,f)==1); }
#include "music_functions.inc"
void expectSaved(const string& name, uint32 position) {
    FILE* f=tmpfile(); assert(f); assert(SaveSoundState(f)); rewind(f);
    uint32 len, pos; assert(fread(&len,4,1,f)==1);
    string actual(len, '\0'); assert(fread(&actual[0],1,len,f)==len);
    assert(fread(&pos,4,1,f)==1); assert(actual==name && pos==position); fclose(f);
}
int main() {
    // A failed backend must retain the intended track through save serialization.
    assert(!PlayMidi("105.mid")); assert(g_dglo.m_lastMusicPath=="105.mid");
    expectSaved("105.mid", 0);
    audio.available=true;
    // This call aliases the string that PlayMidi updates, as LoadSoundState does.
    assert(PlayMidi(g_dglo.m_lastMusicPath.c_str())); expectSaved("105.mid",1234);
    assert(StopMidi()); expectSaved("",0); // intentional silence remains silence
    const string rules="585 105.mid\n617 105.mid\n";
    using dink_music::recoveryTrack;
    assert(recoveryTrack(rules,617,0,true,true,"")=="105.mid");
    assert(recoveryTrack(rules,618,0,true,true,"").empty());
    assert(recoveryTrack(rules,617,-1,true,true,"").empty());
    assert(recoveryTrack(rules,617,1007,true,true,"").empty());
    assert(recoveryTrack(rules,617,0,false,true,"").empty());
    assert(recoveryTrack(rules,617,0,true,false,"").empty());
    assert(recoveryTrack(rules,617,0,true,true,"7.mid").empty());
    for (const string& bad : {"617 ../105.mid\n", "617 105.mid extra\n", "617 /105.mid\n", "617 105.ogg\n"})
        assert(recoveryTrack(bad,617,0,true,true,"").empty());
    FILE* directive=fopen("music-recovery.txt","wb"); assert(directive);
    fputs(rules.c_str(),directive); fclose(directive);
    // Actual load lifecycle: audio is deserialized before attach initializes pmap.
    assert(StopMidi());
    FILE* saved=tmpfile(); assert(saved); assert(SaveSoundState(saved)); rewind(saved);
    pmap=nullptr; assert(LoadSoundState(saved)); fclose(saved);
    assert(g_dglo.m_lastMusicPath.empty() && audio.handle==0);
    assert(GetLocalMusicRecoveryTrack().empty()); // also safe if called too early
    int screen=617; pmap=&screen; // models attach() binding &player_map
    RecoverMusicAfterLoad();
    assert(g_dglo.m_lastMusicPath=="105.mid" && audio.handle!=0);
    expectSaved("105.mid",1234);
    screen=0; assert(GetLocalMusicRecoveryTrack().empty());
    screen=769; assert(GetLocalMusicRecoveryTrack().empty());
    remove("music-recovery.txt");
    puts("PASS: music intent, explicit recovery and null-map save loading lifecycle.");
}
