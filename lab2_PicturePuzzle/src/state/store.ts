import { reducer } from './reducer'
import { configureStore } from '@reduxjs/toolkit'
import { getInitialState } from './state'

export const store = configureStore({
    reducer: reducer,
    devTools: process.env.NODE_ENV !== 'production',
    preloadedState: getInitialState(),
})
