import axios from "axios"

const API_BASE = import.meta.env.VITE_API_BASE

export async function volumeUp() {
    axios.post(`${API_BASE}/volume/up`)
}
export async function volumeDown() {
    axios.post(`${API_BASE}/volume/down`)
}
export async function powerOn() {
    axios.post(`${API_BASE}/power/on`)
}
export async function powerOff() {
    axios.post(`${API_BASE}/power/off`)
}
