Collision = 
{
}

function Collision:OnStart()
	play_audio("Music.wav", true)
end

function Collision:OnUpdate(deltaT)
end

function Collision:OnCollisionEnter(other)
    --print("colliding with "..other)
end

function Collision:OnCollisionExit(other)
    --print("stopped colliding with "..other)
end

-- add this instead of character test
