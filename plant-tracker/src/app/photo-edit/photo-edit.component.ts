import { Component } from "@angular/core";
import { ActivatedRoute, Router } from "@angular/router";
import { Photo, PhotoService } from "../services/photo.service";

@Component({
  selector: "photo-exit",
  template: `
    <ion-header [translucent]="true">
      <ion-toolbar>
        <ion-title> Plant Gallery </ion-title>

        <ion-buttons slot="start">
          <ion-back-button></ion-back-button>
        </ion-buttons>
        <ion-buttons slot="end">
          <ion-button (click)="savePhoto()"> Save </ion-button>
        </ion-buttons>
      </ion-toolbar>
    </ion-header>

    <ion-content>
      <ion-list>
        <ion-item>
          <ion-label position="floating"> Name </ion-label>
          <ion-input
            (ionChange)="photo.name = $event.detail.value"
            value="{{ photo.name }}"
          >
          </ion-input>
        </ion-item>

        <ion-item>
          <ion-label position="floating"> Water Schedule </ion-label>
          <ion-input
            type="number"
            (ionChange)="photo.waterSchedule = $event.detail.value"
            value="{{ photo.waterSchedule }}"
          >
          </ion-input>
        </ion-item>

        <ion-item>
          <ion-label position="floating"> Last Watered </ion-label>
          <ion-datetime
            value="{{ photo.lastWatered }}"
            (ionChange)="photo.lastWatered = $event.detail.value"
            display-timezone="utc"
          ></ion-datetime>
        </ion-item>
      </ion-list>
    </ion-content>
  `,
})
export class PhotoEditComponent {
  private photoId: string = "";
  private photo: Photo;

  constructor(
    private route: ActivatedRoute,
    public photoService: PhotoService,
    private router: Router
  ) {}

  ngOnInit() {
    this.photoId = this.route.snapshot.params["filepath"];
    this.photo = this.getPhoto(this.photoId);
  }

  getPhoto(photoId: string) {
    let id = photoId + ".jpeg";

    return this.photoService.photos.find((e) => e.filepath == id);
  }

  savePhoto() {
    let id = this.photoId + ".jpeg";
    let index = this.photoService.photos.findIndex((e) => e.filepath == id);

    this.photoService.photos[index].name = this.photo.name;
    this.photoService.photos[index].lastWatered = this.photo.lastWatered;
    this.photoService.photos[index].waterSchedule = this.photo.waterSchedule;
    this.photoService.save();

    this.router.navigate(["tabs/tab2"]);
  }
}
