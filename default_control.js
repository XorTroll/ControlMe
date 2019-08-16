
/*

'control' is a global object representing ControlData.

*/

if(control.startupUserAccount == 2)
{
    control.startupUserAccount = 1;
}

control.entries.forEach(function(langentry)
{
    if(langentry.name != null) langentry.name = "Demo JS title";
    if(langentry.author != null) langentry.author = "XorTroll";
});