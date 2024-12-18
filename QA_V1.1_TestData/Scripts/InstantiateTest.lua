InstantiateTest = {

	objectID2
}

function InstantiateTest:OnStart()
	-- instantiate an object with existing uid
    local objectID = instantiate(8, math.random(0, 1280), math.random(0, 720))
    objectID2 = instantiate(8, math.random(0, 1280), math.random(0, 720))
	
	

	-- change the indentifier (name) of the gameObject to make it more readable
	change_gameObject_name(objectID, "BrandNewName")
	change_gameObject_name(1, "player")
	
	-- using the new name to instantiate
	-- you can use instantiate(__self.uid, x, y) on another script to initialise an object name (bullet?) for instantiation later
	local clonedObjectName = instantiate("BrandNewName", math.random(0, 1280), math.random(0, 720)) 
	print(clonedObjectName)

	-- to-do:
	-- Manage/increment unique ids with clones DONE
	-- convert system to use map <uid, gameObjectName> Passes in UID returns gameObjectName
	-- create prefab with enable/disable DONE
	-- helper functions
	print(objectID)
	print(objectID2)
end

function InstantiateTest:OnUpdate( deltaTime )
	local clonedObjectName = instantiate("BrandNewName", math.random(0, 1280), math.random(0, 720)) 
	if(is_key_down("Ionix_P")) then
		disable_object("player")
	end
	if(is_key_down("Ionix_O")) then
		enable_object("player")
	--local clonedObjectName = instantiate("BrandNewName", math.random(0, 1280), math.random(0, 720)) 
	
	if (is_key_down("Ionix_Q")) then
		--remove_object(objectID2)
		log("Q pressed")
	end

	if (is_key_down("Ionix_R")) then
		--objectID2 = instantiate (8, 250, 400)
	end

	if (is_mouse_down("Ionix_Mouse0")) then
		log("mouse pressed")
	end
end