level_generator =
{
    nx = 128,
    ny = 64,
    tile_size = 64,
    level_map = {},
    tile_prototypes = {"Tile1Proto","Tile2Proto"},
    wall_indices = {8,10,0,9,13,1,7,11,3,14,4,2,6,5,4}
}

function level_generator:OnStart()
    -- find the tile prototypes

    -- create a 2d array for the level map
    for i = 1,self.nx do
        self.level_map[i] = {}
        for j = 1,self.ny do
            self.level_map[i][j] = 0
        end
    end 

    -- now use perlin noise to populate the matrix

    xorigin = -self.nx * self.tile_size / 2
    yorigin = -self.ny * self.tile_size / 2

    mean_noise = 0
    for i = 1, self.nx do
        x = xorigin + i * self.tile_size
        for j = 1, self.ny do
            y = yorigin + j * self.tile_size
            -- get perlin noise value for here
            self.level_map[i][j] = PerlinNoise( x, y, self.tile_size * 5 )
            mean_noise = mean_noise + self.level_map[i][j]
        end
    end
    mean_noise = mean_noise/(self.nx*self.ny)
    for i = 1, self.nx do
        for j = 1, self.ny do
            if (self.level_map[i][j] < mean_noise) then
                self.level_map[i][j] = 0
            else
                self.level_map[i][j] = 1
            end
        end
    end
    -- spawn tiles
    for i = 1, self.nx do
        x = xorigin + i * self.tile_size
        for j = 1, self.ny do
            y = yorigin + j * self.tile_size
            if (self.level_map[i][j] == 0) then
                obj_name, nx, ny = instantiate(self.tile_prototypes[1], x, y)
            else
                obj_name, nx, ny = instantiate(self.tile_prototypes[2], x, y)
            end
            -- update the texture on this tile
            if self.level_map[i][j] == 0 then
                -- this is floor
                tile = math.random(6)-1
                tile_tex = "dungeons2.png_tile_"..tostring(tile)
                set_texture( uid_from_name(obj_name), tile_tex)
            else
                tile_index = 0
                if i > 1 and self.level_map[i-1][j] == 0 then
                    tile_index = tile_index+1
                end
                if j > 1 and self.level_map[i][j-1] == 0 then
                    tile_index = tile_index+2
                end
                if i < self.nx and self.level_map[i+1][j] == 0 then
                    tile_index = tile_index+4
                end
                if j < self.ny and self.level_map[i][j+1] == 0 then
                    tile_index = tile_index+8
                end
                if tile_index == 0 then
                    tile = math.random(6)-1
                    tile_tex = "dungeons3.png_tile_"..tostring(tile)
                    set_texture( uid_from_name(obj_name), tile_tex)
                else
                    tile_tex = "dungeons.png_tile_"..tostring(self.wall_indices[tile_index])
                    set_texture( uid_from_name(obj_name), tile_tex)
                end
            end
        end
    end

end

function level_generator:OnUpdate()

end