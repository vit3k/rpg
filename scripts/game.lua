local MovementSystem = import('movementSystem')
local InputSystem = import('inputSystem')
local PlayerSystem = import('playerSystem')
local game = {}

function game:init()
	-- clearWorld() needs to be added when changing states will be available

	--local inputSystem = registerSystem(InputSystem)
	--local movementSystem = registerSystem(MovementSystem)
	local playerSystem = registerSystem(PlayerSystem)

	print('game init')
	local player = createEntity({
			transform = { x = 0, y = 0 },
			player = {},
			sprite = {
				spritesheets = {
					idle = {
						texture = 'Resources/Skeleton Idle.png',
						spritesCount = 11,
						spriteSize = { x = 24, y = 32}
					}
				}
			},
			animation = {
				animations = {
					idle = {
						spritesheet = 'idle',
						frames = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10},
						fps = 11,
						loop = true
					}
				},
				currentAnimation = 'idle'
			}
		})
end

return game