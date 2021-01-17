import { Component } from "@angular/core";
import { Photo, PhotoService } from "../services/photo.service";
import { Router } from "@angular/router";

@Component({
  selector: "app-tab2",
  templateUrl: "tab2.page.html",
  styleUrls: ["tab2.page.scss"],
})
export class Tab2Page {
  constructor(public photoService: PhotoService, private router: Router) {}

  async ngOnInit() {
    await this.photoService.loadSaved();
  }

  addPhotoToGallery() {
    this.photoService.addNewToGallery();
  }

  buttonColor(date: Date, schedule: number) {
    let newDate = new Date();
    let oldDate = new Date(date);
    let x = new Date(
      oldDate.getFullYear(),
      oldDate.getMonth(),
      oldDate.getDate() + Number(schedule)
    );

    let dateDiff = newDate.getDate() - x.getDate();

    if (dateDiff === 0) {
      return "success";
    }
    if (dateDiff >= 0) {
      return "danger";
    }
    if (dateDiff <= 0) {
      return "primary";
    }
  }

  fixDate(date: Date, schedule: number) {
    let newDate = new Date();
    let oldDate = new Date(date);
    let x = new Date(
      oldDate.getFullYear(),
      oldDate.getMonth(),
      oldDate.getDate() + Number(schedule)
    );

    let dateDiff = newDate.getDate() - x.getDate();

    if (dateDiff === 0) {
      return "Water Today";
    }
    if (dateDiff >= 0) {
      return "Water is " + dateDiff + " days late!";
    }
    if (dateDiff <= 0) {
      return Math.abs(dateDiff) + " days untill water!";
    }
    if (x > newDate) {
      let diffTimeSinceLastWatered = Math.abs(newDate.getTime() - x.getTime());
      const diffDaysSinceLastWatered = Math.round(
        diffTimeSinceLastWatered / (1000 * 60 * 60 * 24)
      );
      console.log(diffDaysSinceLastWatered);
      return diffDaysSinceLastWatered + " days left until water";
    } else if (newDate > x) {
      let qq = Math.abs(newDate.getTime() - x.getTime());
      const diffDaysSinceLastWatered = Math.round(qq / (1000 * 60 * 60 * 24));
      return " should be watered " + diffDaysSinceLastWatered + " days ago";
    }

    return "Fail";
  }

  editPlant(plant: Photo) {
    this.router.navigate([
      "tabs/tab2/edit/" + plant.filepath.replace(".jpeg", ""),
    ]);
  }

  waterPlant(p: Photo) {
    p.lastWatered = new Date();
    this.photoService.save();
  }
}
