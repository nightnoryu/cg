import { Dimensions, Level, Tiles } from './types'

export const IMAGE_WIDTH = 500
export const IMAGE_HEIGHT = 500

// TODO: describe as data structure
export function getImagePath(level: Level): string {
    let path = '/img/'

    switch (level) {
        case Level.FIRST:
            path += 'winter_car.jpg'
            break
        case Level.SECOND:
            path += 'suburban_landscape.jpg'
            break
        case Level.THIRD:
            path += 'village.jpg'
            break

        case Level.FOURTH:
            path += 'room.jpg'
            break
        case Level.FIFTH:
            path += 'sunny_room.jpg'
            break
        case Level.SIXTH:
            path += 'pc_setup.jpg'
            break

        case Level.SEVENTH:
            path += 'lea_smug.jpg'
            break
        case Level.EIGHTH:
            path += 'konoko.jpg'
            break
        case Level.NINTH:
            path += 'jill.jpg'
            break
    }

    return process.env.PUBLIC_URL + path
}

export function getDimensions(level: Level): Dimensions {
    switch (level) {
        case Level.FIRST:
        case Level.SECOND:
        case Level.THIRD:
            return {
                width: 4,
                height: 4,
            }
        case Level.FOURTH:
        case Level.FIFTH:
        case Level.SIXTH:
            return {
                width: 5,
                height: 5,
            }
        case Level.SEVENTH:
        case Level.EIGHTH:
        case Level.NINTH:
            return {
                width: 6,
                height: 6,
            }
    }
}

export function getTileDimensions(dimensions: Dimensions): Dimensions {
    return {
        width: IMAGE_WIDTH / dimensions.width,
        height: IMAGE_HEIGHT / dimensions.height,
    }
}

export function shuffleTiles(level: Level): Tiles {
    const dimensions = getDimensions(level)
    const tileDimensions = getTileDimensions(dimensions)

    const tiles: Tiles = []
    for (let i = 0; i < dimensions.width * dimensions.height; ++i) {
        tiles.push({
            index: i,
            top: -(Math.floor(i / dimensions.height)) * tileDimensions.height,
            left: (-i % dimensions.width) * tileDimensions.width,
        })
    }

    const length = tiles.length
    for (let i = 0; i < length; ++i) {
        const index = Math.floor(Math.random() * (length - 1))
        const item = tiles.splice(index, 1)
        tiles.push(item[0])
    }

    return tiles
}
