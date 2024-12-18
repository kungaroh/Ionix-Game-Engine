coroutines = {}

coroutinewaits = {}

localmap = {}

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





function import_from_map( map )

       --log("  ")
       --log("  ")
       --log("  ")
       --log("  ")
       --log("--------LAYER LOOP DATA-----------")
      
		width = map.width
		height = map.height
		tileWidth = map.tilewidth
		tileHeight = map.tileheight
		map_tile_size_import(tileWidth, tileHeight, width, height)
		
        for i,v in pairs(map.tilesets) do
            --Tile set import
            --Creates tile set struct with firstgid and filename then adds it to tiledData
            firstgid = map.tilesets[i].firstgid
            filename = map.tilesets[i].name
            tile_set_import(firstgid, filename)
        end

        for i,v in pairs(map.layers) do
        --log(i..":"..tostring(v))
        --log("--------NEW OBJECT GROUP-----------")
            --TiledLayer name
            map_layer_import(map.layers[i].name)
			
			
			
            --Layer properties
            for k, v in pairs(map.layers[i].properties) do
                message="property: "..tostring(k).." "..tostring(v)
                --log(message)
                layer_properties(tostring(k), tostring(v))
                --Method for getting k & v add them in as we get them using this method
            end

            if map.layers[i].data ~= nil then
                for i, v in ipairs(map.layers[i].data) do
                    --Add data to array in struct
                    add_tile_map_id_data(v)
                end
            end

            if map.layers[i].objects ~= nil then
                for j, object in pairs(map.layers[i].objects) do
                    
                    --log(iterator2..":"..tostring(value2))
                    --log("--------NEW OBJECT-----------")
                    x = object.x
                    y = object.y
                    width = object.width
                    height = object.height
                    visible = object.visible
                    name = object.name
                    gid = object.gid
                    message = "object: name:"..name.." x:"..tostring(x).." y:"..tostring(y)..
                        " width:"..tostring(width).." height:"..tostring(height)..
                        " visible:"..tostring(visible).."gid:"..tostring(gid)
                    --log(message)
                    map_variable_import(x,y,width,height,visible,name, gid)
                    for k, v in pairs(object.properties) do
                        message="property: "..tostring(k).." "..tostring(v)
                        --log(message)
                        object_properties(tostring(k), tostring(v))
                        --Method for getting k & v add them in as we get them using this method
                    end

                    add_object_to_layer()
                    --function to pass object into c++
                end

            end

            --Add layer to TiledData
            add_layer_to_data()
       end
       --Call Jimmy's even
       call_tiled_import_event()
end