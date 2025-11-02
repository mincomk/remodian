import { volumeDown, volumeUp } from "../api";
import { Button } from "./ui/button";

export function VolumeControl() {
    return (
        <div className="flex flex-row gap-3">
            <Button singleFunction={volumeDown} multiFunction={volumeDown}>V-</Button>
            <Button singleFunction={volumeUp} multiFunction={volumeUp}>V+</Button>
        </div>
    )
}
