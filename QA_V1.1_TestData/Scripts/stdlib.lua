coroutines = {}

coroutinewaits = {}

function CreateCoroutine(func, args)
    co = coroutine.create(func)
    table.insert(coroutines, co)
    coroutine.resume(co, args)
end

function UpdateCoroutines( deltaTime )
    --Check status resume if suspended
    for i,coroutineName in pairs(coroutines) do
        if (coroutine.status(coroutineName) == "dead") then
            table.remove(coroutines, co)
        end
        if (coroutine.status(coroutineName) == "suspended") then
            if coroutinewaits[coroutineName] <= 0 then
                coroutine.resume(coroutineName)
            else
                coroutinewaits[coroutineName] = coroutinewaits[coroutineName] - deltaTime
            end
        end
    end
end

function YieldNextUpdate()
    tr = coroutine.running()
    coroutinewaits[tr] = 0
    coroutine.yield()
end

function YieldWaitForSeconds( time )
    tr = coroutine.running()
    coroutinewaits[tr] = time
    coroutine.yield()
end

function WaitForScondsRealtime()

end