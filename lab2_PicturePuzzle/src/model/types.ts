export enum Level { // TODO: simplify adding levels
    FIRST,
    SECOND,
    THIRD,
    FOURTH,
    FIFTH,
    SIXTH,
    SEVENTH,
    EIGHTH,
    NINTH,
}

export type Tile = {
    index: number
    top: number // TODO: extract
    left: number
}

export type Tiles = Tile[]

export type Dimensions = {
    width: number
    height: number
}

// TODO: improve state (several entities in one place)
export type Game = {
    level: Level
    tiles: Tiles

    dimensions: Dimensions
    tileDimensions: Dimensions // TODO: improve calculating tile dimensions

    imagePath: string

    isLevelFinished: boolean
    isFinished: boolean
}
