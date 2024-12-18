collision_test = {
    manager_uid = 0
}

function collision_test:OnStart()
    self.manager_uid = uid_from_name("gamemanager")
    log("manager uid is "..tostring(self.manager_uid))
end

function collision_test:OnUpdate( deltaTime )
end

function collision_test:OnTriggerEnter( otherUID )
    message = "OnTriggerEnter called on ".. tostring(self.__uid) .. " - other object is " .. tostring(otherUID)
    print(message)
end

function collision_test:OnTriggerExit( otherUID )
    message = "OnTriggerExit called on "..tostring(self.__uid).." - other object is "..tostring(otherUID)
    print(message)
end

function collision_test:OnCollisionEnter( otherUID )
    message = "OnCollisionEnter called on "..tostring(self.__uid).." - other object is "..tostring(otherUID)

    call_function( "game_manager", "IncrementCounter", self.manager_uid )
    print(message)
end

function collision_test:OnCollisionExit( otherUID )
    message = "OnCollisionExit called on "..tostring(self.__uid).." - other object is "..tostring(otherUID)
    print(message)
end