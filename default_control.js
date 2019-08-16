
/*

'control' is a global object representing ControlData.

*/

function changeNameIfPresent(name) // Some NACP langnuage entry fields won't be present (sent as null by ControlMe) so omit those
{
    control.entries.forEach(function(langentry)
    {
        if(langentry.name != null) langentry.name = name;
    });
}

function specificTitleDemo()
{
    // Set a custom name if application ID matches SMO's one
    if(control.applicationId == "0100000000010000")
    {
        changeNameIfPresent("Sup Mama Odyssey"); // XD
    }
}

function avoidLinkedAccounts()
{
    // startupUserAccount value 2 = needs account which has Nintendo services linked, so change that to 1 = needs account, doesnt matter if linked or not
    if(control.startupUserAccount == 2)
    {
        control.startupUserAccount = 1;
    }
}

function applicationIdTest()
{
    // Change every title's name for their application ID (stringified, of course)
    changeNameIfPresent(control.applicationId);
}

// Run as may tests as you want here

avoidLinkedAccounts();
applicationIdTest();
specificTitleDemo();