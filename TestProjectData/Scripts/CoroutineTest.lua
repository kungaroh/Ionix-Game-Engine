-- basic format is to include serializable variables in the table at the top.
-- Object name should be the same as the file name.
-- This object will be cloned - a 'new' function will be added to it at load time
CoroutineTest = 
{
    -- add initial variables here
    x = 3
}

function CoroutineTest:Test()
    while true do
        print("hello")
        print(self.x)
        YieldWaitForSeconds(5)
    end
end
function CoroutineTest:OnStart()
    log("Start Coroutine Test")

    CreateCoroutine(CoroutineTest.Test, self)
end

function CoroutineTest:OnUpdate(deltaTime)

end
