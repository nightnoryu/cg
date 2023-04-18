import React from 'react'
import Image from './components/Image/Image'
import Controls from './components/Controls/Controls'
import styles from './App.module.css'

function App() {
    return (
        <div className={styles.app}>
            <Image />
            <Controls />
        </div>
    )
}

export default App
