import React from 'react'
import { actionCreators } from '../../state/actions/actionCreators'
import { Dispatch } from 'redux'
import { Action } from '../../state/actions/actions'
import { connect } from 'react-redux'
import { Level } from '../../model/types'
import { RootState } from '../../state/state'
import styles from './Controls.module.css'

type ControlsStateProps = {
    level: Level
    isLevelFinished: boolean
    isFinished: boolean
}

type ControlsDispatchProps = {
    newGame: () => void
    nextLevel: () => void
}

type ControlsProps = ControlsStateProps & ControlsDispatchProps

function Controls({ level, isLevelFinished, isFinished, newGame, nextLevel }: ControlsProps) {
    return (
        <div>
            <h1 className={styles.message}>Level {level + 1}</h1>

            <button onClick={newGame} className={styles.button}>
                New Game
            </button>

            {
                isLevelFinished &&
                <>
                    <h1 className={styles.message}>Level completed!</h1>
                    <button onClick={nextLevel} className={styles.button}>
                        Next
                    </button>
                </>
            }

            {
                isFinished &&
                <h1 className={styles.message}>YOU WON!!!</h1>
            }
        </div>
    )
}

function mapStateToProps(state: RootState): ControlsStateProps {
    return {
        level: state.level,
        isLevelFinished: state.isLevelFinished,
        isFinished: state.isFinished,
    }
}

function mapDispatchToProps(dispatch: Dispatch<Action>): ControlsDispatchProps {
    return {
        newGame: () => actionCreators.newGame()(dispatch),
        nextLevel: () => actionCreators.nextLevel()(dispatch),
    }
}

export default connect(mapStateToProps, mapDispatchToProps)(Controls)
