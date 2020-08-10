local MovementSystem = import('movementSystem')
local PlayerSystem = import('playerSystem')
local game = {}

function game:init()
	Input.defineAction('move_left', Key.A)
	Input.defineAction('move_right', Key.D)

	local playerSystem = registerSystem(PlayerSystem)
	local movementSystem = registerSystem(MovementSystem)

	print('game init')
	local player = createEntity({
			transform = { x = 0, y = 800 },
			player = {},
			velocity = {
				velocity = { x = 0, y = 0}
			},
			sprite = {
				spritesheets = {
					idle = {
						texture = 'Resources/Skeleton Idle.png',
						spritesCount = 11,
						spriteSize = { x = 24, y = 32}
					},
					walk = {
						texture = 'Resources/Skeleton Walk.png',
						spritesCount = 13,
						spriteSize = { x = 22, y = 33}
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
					},
					walk = {
						spritesheet = 'walk',
						frames = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12},
						fps = 13,
						loop = true
					}
				},
				currentAnimation = 'idle'
			}
		})
	print('player created')
end

return game