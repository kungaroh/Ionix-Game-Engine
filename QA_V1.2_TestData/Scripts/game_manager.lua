game_manager = {
    hits = 0,
    kills = 0
}

function game_manager:OnStart()
    add_label("Hits: "..tostring(self.hits).." Kills: "..tostring(self.kills), 10, 10, 1, 2)
    CreateCoroutine( game_manager.SpawnEnemyWaves, self )
end

function game_manager:OnUpdate(deltaTime)
    update_ui_text(1, "Hits: "..tostring(self.hits).." Kills: "..tostring(self.kills))
end

function game_manager:SpawnEnemyWaves()
    while (true) do
        -- spawn a wave
        wavePos = 20 + math.random()*600
        for i = 0, 9 do
            x = wavePos + i * 64
            y = -32 -i*8
            instantiate( "EnemyPrefab", x, y)
        end
        YieldWaitForSeconds(3 + math.random()*3)
    end
end

function game_manager:RegisterHit()
    self.hits = self.hits + 1
end

function game_manager:RegisterKill()
    self.kills = self.kills + 1
end