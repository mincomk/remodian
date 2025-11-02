import axios from "axios"

const API_BASE = "http://localhost:1023" // TODO change

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
