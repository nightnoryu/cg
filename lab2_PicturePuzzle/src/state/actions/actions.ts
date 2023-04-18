export enum ActionType {
    NEW_GAME,
    SWAP_TILES,
    NEXT_LEVEL,
}

export type Action = {
    type: ActionType
    payload?: any
}
