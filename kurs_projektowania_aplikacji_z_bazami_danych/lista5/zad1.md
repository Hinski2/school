## pierwotnie: 
![](img/i1.png)
* ID
* Patient
* Patient Address
* Appointment time and location 
* Price
* Physician 
* Appointment cause

---

## 1NF

* ID

* PatientFirstName
* PatienLastname

* PatientStreen
* PatientPostalCode
* PatientCity

* AppointmentDate
* AppointmentTime
* AppointmentRoom

* Price 

* PhysicianFirstName
* PhysicianLastName

* AppointmentSpecification
* AppointmetnDescription

---- 

## 2NF
#### Patient

* PatientID `pk`
* FirstName
* LastName
* Street
* PostalCode
* Cityj

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

* Specialization
* AppointmentDescription

----

## 3NF
#### Patient

* PatientID `pk`
* FirstName
* LastName
* Street
* PostalCode
* Cityj

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