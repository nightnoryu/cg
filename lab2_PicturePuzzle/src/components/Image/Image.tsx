import React, { useState } from 'react'
import styles from './Image.module.css'
import { RootState } from '../../state/state'
import { Dimensions, Tiles } from '../../model/types'
import { Dispatch } from 'redux'
import { Action } from '../../state/actions/actions'
import { actionCreators } from '../../state/actions/actionCreators'
import { connect } from 'react-redux'
import { IMAGE_HEIGHT, IMAGE_WIDTH } from '../../model/helpers'

type ImageStateProps = {
    tiles: Tiles
    imagePath: string
    tileDimensions: Dimensions
    isFinished: boolean
}

type ImageDispatchProps = {
    swapTiles: (index1: number, index2: number) => void,
}

type ImageProps = ImageStateProps & ImageDispatchProps

function Image({ tiles, imagePath, tileDimensions, isFinished, swapTiles }: ImageProps) {
    const [selectedTile, setSelectedTile] = useState<number | null>(null)

    const handleClick = (index: number) => {
        if (isFinished) {
            return
        }

        if (selectedTile === null) {
            setSelectedTile(index)
            return
        }

        swapTiles(selectedTile, index)
        setSelectedTile(null)
    }

    return (
        <div
            className={styles.image}
            style={{
                width: IMAGE_WIDTH + 50,
                height: IMAGE_HEIGHT,
            }}
        >
            {tiles.map((tile, i) => (
                <div
                    key={tile.index}
                    className={`${styles.tile} ${selectedTile === i ? ` ${styles.selected}` : ''}`}
                    onClick={() => handleClick(i)}
                    style={{
                        width: tileDimensions.width,
                        height: tileDimensions.height,
                    }}
                >
                    {/* TODO: research about memory consumption */}
                    <img
                        src={imagePath}
                        alt="tile"
                        className={styles.tileImage}
                        style={{
                            width: IMAGE_WIDTH,
                            height: IMAGE_HEIGHT,
                            top: tile.top,
                            left: tile.left,
                        }}
                    />
                </div>
            ))}
        </div>
    )
}

function mapStateToProps(state: RootState): ImageStateProps {
    return {
        tiles: state.tiles,
        imagePath: state.imagePath,
        tileDimensions: state.tileDimensions,
        isFinished: state.isFinished,
    }
}

function mapDispatchToProps(dispatch: Dispatch<Action>): ImageDispatchProps {
    return {
        swapTiles: (index1: number, index2: number) => actionCreators.swapCells(index1, index2)(dispatch),
    }
}

export default connect(mapStateToProps, mapDispatchToProps)(Image)
