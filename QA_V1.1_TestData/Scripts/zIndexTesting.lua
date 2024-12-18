zIndexTesting = {

    x = 200,
    y = 200
}


function zIndexTesting:OnStart()
    -- set the position of the parent
    set_object_position( self.__uid, self.x, self.y)
end


function zIndexTesting:OnUpdate( deltaTime )

end