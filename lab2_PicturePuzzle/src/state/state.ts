import { Game, Level } from '../model/types'
import { getDimensions, getImagePath, IMAGE_HEIGHT, IMAGE_WIDTH, shuffleTiles } from '../model/helpers'

export function getInitialState(): Game {
    const level = Level.FIRST

    const dimensions = getDimensions(level)
    const tileWidth = IMAGE_WIDTH / dimensions.width
    const tileHeight = IMAGE_HEIGHT / dimensions.height

    return {
        level: level,
        tiles: shuffleTiles(level),

        dimensions: dimensions,
        tileDimensions: {
            width: tileWidth,
            height: tileHeight,
        },

        imagePath: getImagePath(level),

        isLevelFinished: false,
        isFinished: false,
    }
}

export type RootState = ReturnType<typeof getInitialState>
