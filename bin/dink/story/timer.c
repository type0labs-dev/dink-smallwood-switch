//count five seconds, then kill the notification
void main
{
int &script = &juggle
wait(5000)
run_script_by_number(&script, "remove")
kill_this_task()
}