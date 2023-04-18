import { Game, Level, Tiles } from './types'
import { getInitialState } from '../state/state'
import { getDimensions, getImagePath, getTileDimensions, shuffleTiles } from './helpers'

export function newGame(): Game {
    return getInitialState()
}

export function swapTiles(game: Game, index1: number, index2: number): Game {
    const tile1 = game.tiles[index1]
    const tile2 = game.tiles[index2]

    const newTiles = [...game.tiles]
    newTiles[index2] = tile1
    newTiles[index1] = tile2

    if (isPuzzleComplete(newTiles)) {
        if (game.level === Level.NINTH) {
            return {
                ...game,
                tiles: newTiles,
                isFinished: true,
            }
        }

        return {
            ...game,
            isLevelFinished: true,
        }
    }

    return {
        ...game,
        tiles: newTiles,
    }
}

export function nextLevel(game: Game): Game {
    const newLevel = game.level + 1
    const newDimensions = getDimensions(newLevel)

    return {
        ...game,
        level: newLevel,
        tiles: shuffleTiles(newLevel),

        dimensions: newDimensions,
        tileDimensions: getTileDimensions(newDimensions),

        imagePath: getImagePath(newLevel),

        isLevelFinished: false,
    }
}

// TODO: improve complexity < O(n)
function isPuzzleComplete(tiles: Tiles): boolean {
    for (let i = 0; i < tiles.length; ++i) {
        if (i !== tiles[i].index) {
            return false
        }
    }

    return true
}
