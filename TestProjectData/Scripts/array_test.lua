array_test = {}
array_test.__index = array_test

function array_test:new()
    local obj = setmetatable({}, self)
    return obj
end

function array_test:OnStart()
    print("Script started!")
    local arr = return_int_array()
    for i, v in ipairs(arr) do
        print("Index: " .. i .. ", Value: " .. v)
    end
end

function array_test:OnUpdate(dt)
   
end