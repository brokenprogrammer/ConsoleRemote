import { NgModule } from "@angular/core";
import { RouterModule, Routes } from "@angular/router";
import { PhotoEditComponent } from "../photo-edit/photo-edit.component";
import { Tab2Page } from "./tab2.page";

const routes: Routes = [
  {
    path: "",
    component: Tab2Page,
  },
  {
    path: "edit/:filepath",
    component: PhotoEditComponent,
  },
];

@NgModule({
  imports: [RouterModule.forChild(routes)],
  exports: [RouterModule],
})
export class Tab2PageRoutingModule {}
