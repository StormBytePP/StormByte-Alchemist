function Component()
{
}

Component.prototype.isDefault = function()
{
    // select the component by default
    return true;
}

Component.prototype.createOperations = function()
{
    component.createOperations();

    if (systemInfo.productType === "windows")
    {
        component.addElevatedOperation("Execute", "{0,1,256}", "@TargetDir@/bin/vc_redist.x64.exe", "/install", "/quiet", "/norestart");
        component.addElevatedOperation("Delete", "@TargetDir@/bin/vc_redist.x64.exe");
		component.addOperation("CreateShortcut", "@TargetDir@/bin/Alchemist.exe", "@StartMenuDir@/Alchemist.lnk", "workingDirectory=@TargetDir@");
        component.addOperation("CreateShortcut", "@TargetDir@/bin/Alchemist.exe", "@HomeDir@/Desktop/Alchemist.lnk");
    }
}

