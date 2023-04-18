import { getInitialState } from './state'
import { Action, ActionType } from './actions/actions'
import { newGame, nextLevel, swapTiles } from '../model/actions'

export function reducer(state = getInitialState(), action: Action) {
    switch (action.type) {
        case ActionType.NEW_GAME:
            return newGame()
        case ActionType.SWAP_TILES:
            return swapTiles(state, action.payload.index1, action.payload.index2)
        case ActionType.NEXT_LEVEL:
            return nextLevel(state)
        default:
            return state
    }
}
