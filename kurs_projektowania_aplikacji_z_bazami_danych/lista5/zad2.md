## 3NF
#### Patient

* PatientID `pk`
* FirstName
* LastName
* Street
* PostalCode
* Cityj

* TotalAppointments
* TotalAmount

#### Phisician

* PhisicianID `pk`
* FirstName
* LastName

#### Appointment

* AppointmentId `pk`
* PatientId `fk -> Patient::PatientID`
* PhisicianId `fk -> Physician::PhysicianId`

* AppointmentDate
* AppointmentTime
* AppointmentRoom

* Price

* AppointmentDescription

#### PhysicianSpecialization

* PhysicianID `fk -> Physician::PhysicianID`
* SpecializationId `fk -> Specialization::SpecializationID` 

#### Specialization

* specializationId `pk`
* specializationName 

--- 