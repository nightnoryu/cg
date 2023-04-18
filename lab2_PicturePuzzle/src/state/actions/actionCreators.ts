import { Dispatch } from 'redux'
import { Action, ActionType } from './actions'

export const actionCreators = {
    newGame() {
        return (dispatch: Dispatch<Action>) => {
            dispatch({
                type: ActionType.NEW_GAME,
            })
        }
    },

    swapCells(index1: number, index2: number) {
        return (dispatch: Dispatch<Action>) => {
            dispatch({
                type: ActionType.SWAP_TILES,
                payload: {
                    index1,
                    index2,
                },
            })
        }
    },

    nextLevel() {
        return (dispatch: Dispatch<Action>) => {
            dispatch({
                type: ActionType.NEXT_LEVEL,
            })
        }
    },
}
