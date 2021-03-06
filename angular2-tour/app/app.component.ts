import { Component } from '@angular/core';

@Component({
    selector: 'my-app',
    template:` <h1>{{title}}</h1>
		<h2>{{company.name}} details!</h2>
		<div><label>id: </label>{{company.id}}</div>
		<div>
		  <label>name: </label>
		  <input [(ngModel)]="company.name" placeholder="name">
		</div>
  		`
})
export class AppComponent {
    title = 'Angular 2 Tour';
    company: Company = {
   	id: 1;
   	name: 'SAP AG'
    }
    
}

