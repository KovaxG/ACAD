; Proiect LISP
; Kovacs Gyorgy

; Degrees to Radians
(deFun d2r (d)
  (/ (* d (* 2 pi)) 360.0)
)

; Radians to Degrees
(deFun r2d (r)
  (/ (* 360 r) (* 2 pi))
)

; Used for getting points from users
(deFun inputPoint(message / x y cursorStuff)
  (princ message)
  (setq cursorStuff (grread nil 2 0))
  (setq x (caadr cursorStuff))
  (setq y (cadadr cursorStuff))
  (list x y)
)

; Returns the middle of 2 points
(deFun getMidPoint (point1 point2)
  (list (/ (+ (car endPoint) (car startPoint)) 2) (/ (+ (cadr endPoint) (cadr startPoint)) 2))
)

; By providing a start and end point we get a DC voltage source
(deFun C:E_VS()(C:E_VoltageSource))
(deFun C:E_VoltageSource(/ startPoint endPoint midPoint p1 p2 r thisAngle)
  (setq r 1)
  (setq startPoint (inputPoint "\n Enter the start point:")) ; Get the starting point
  (setq endPoint (inputPoint "\n Enter the end point")) ; Get the end point
  (setq midPoint (getMidPoint startPoint endPoint)) ; Calculate the middle point
  (setq thisAngle (angle startPoint endPoint)) ; Get the angle

  (setq p1 (list (- (car midPoint) (* r (cos thisAngle))) (- (cadr midPoint) (* r (sin thisAngle))))) ; Compute first point
  (setq p2 (list (+ (car midPoint) (* r (cos thisAngle))) (+ (cadr midPoint) (* r (sin thisAngle))))) ; Compute second point

  (command "CIRCLE" midPoint r "")
  (command "PLINE" startPoint p1 "")
  (command "PLINE" p2 endPoint "")
  (command "PLINE" (polar midPoint (+ thisAngle (d2r 90)) r) (polar midPoint (- thisAngle (d2r 90)) r) "")
  (princ)
)

; DC current source
(deFun C:E_CS()(C:E_CurrentSource))
(deFun C:E_CurrentSource(/ startPoint endPoint midPoint)
  (setq r 1)
  (setq startPoint (inputPoint "\n Enter the start point:")) ; Get the starting point
  (setq endPoint (inputPoint "\n Enter the end point")) ; Get the end point
  (setq midPoint (getMidPoint startPoint endPoint)) ; Calculate the middle point

  (command "CIRCLE" midPoint r "")
  (command "PLINE" startPoint endPoint "")

  (princ)
)

; The ground
(deFun C:E_GND(/ midPoint p1 r)
  (setq r 1)
  (setq r (/ r 2.0))
  (setq midPoint (inputPoint "\n Enter the middle point: "))
  (setq p1 (polar midPoint (d2r 270) r))

  (command "PLINE" midPoint (polar midPoint (d2r 270) r) "")
  (command "PLINE" (polar p1 (d2r 180) r) (polar p1 (d2r 0) r) "")
  (setq p1 (polar p1 (d2r 270) (/ r 3.0)))
  (command "PLINE" (polar p1 (d2r 180) (* r (/ 2.0 3.0))) (polar p1 (d2r 0) (* r (/ 2.0 3.0))) "")
  (setq p1 (polar p1 (d2r 270) (/ r 3.0)))
  (command "PLINE" (polar p1 (d2r 180) (/ r 3.0)) (polar p1 (d2r 0) (/ r 3.0)) "")
  
  (princ)
)

; An electrical resistor
(deFun C:E_R()(C:E_RESISTOR))
(deFun C:E_RESISTOR(/ r startPoint endPoint midPoint thisAngle p1 p2)
  (setq r 1)
  (setq startPoint (inputPoint "\n Enter the start point:")) ; Get the starting point
  (setq endPoint (inputPoint "\n Enter the end point")) ; Get the end point
  (setq midPoint (getMidPoint startPoint endPoint)) ; Calculate the middle point
  (setq thisAngle (angle startPoint endPoint)) ; Get the angle

  (setq p1 (list (- (car midPoint) (* r (cos thisAngle))) (- (cadr midPoint) (* r (sin thisAngle))))) ; Compute first point
  (setq p2 (list (+ (car midPoint) (* r (cos thisAngle))) (+ (cadr midPoint) (* r (sin thisAngle))))) ; Compute second point

  (command "PLINE" startPoint p1
	   (setq p1 (polar p1 (+ thisAngle (d2r 90)) (/ r 2.0)))
	   (setq p1 (polar p1 thisAngle (* r 2.0)))
	   (setq p1 (polar p1 (- thisAngle (d2r 90)) r))
 	   (setq p1 (polar p1 (- thisAngle (d2r 180)) (* r 2.0)))
	   (setq p1 (polar p1 (+ thisAngle (d2r 90)) (/ r 2.0)))
  "")
  (command "PLINE" p2 endPoint "")
  
  (princ)
)

; An electrical coil
(deFun C:E_COIL(/ endPoint startPoint midPoint thisAngle p1 p2)
  (setq r 1.0)
  (setq startPoint (inputPoint "\n Enter the start point:")) ; Get the starting point
  (setq endPoint (inputPoint "\n Enter the end point")) ; Get the end point
  (setq midPoint (getMidPoint startPoint endPoint)) ; Calculate the middle point
  (setq thisAngle (angle startPoint endPoint)) ; Get the angle

  (setq p1 (list (- (car midPoint) (* r (cos thisAngle))) (- (cadr midPoint) (* r (sin thisAngle))))) ; Compute first point
  (setq p2 (list (+ (car midPoint) (* r (cos thisAngle))) (+ (cadr midPoint) (* r (sin thisAngle))))) ; Compute second point

  (command "PLINE" startPoint p1 "")
  (command "ARC" p1 "c" (polar p1 thisAngle (/ r 3.0)) (polar p1 thisAngle (* r (/ 2.0 3.0))) "")
  (command "ARC" (polar p1 thisAngle (* r (/ 2.0 3.0))) "c" (polar p1 thisAngle r) (polar p1 thisAngle (* r (/ 4.0 3.0))) "")
  (command "ARC" (polar p1 thisAngle (* r (/ 4.0 3.0))) "c" (polar p1 thisAngle (* r (/ 5.0 3.0))) p2 "")
  (command "PLINE" p2 endPoint "")
  (princ)
)

; Electrical capacitor
(deFun C:E_CAP()(C:E_CAPACITOR))
(deFun C:E_CAPACITOR(/ r startPoint endPoint midPoint thisAngle p1 p2)
  (setq r 1.0)
  (setq r (/ r 3.0))
  (setq startPoint (inputPoint "\n Enter the start point:")) ; Get the starting point
  (setq endPoint (inputPoint "\n Enter the end point")) ; Get the end point
  (setq midPoint (getMidPoint startPoint endPoint)) ; Calculate the middle point
  (setq thisAngle (angle startPoint endPoint)) ; Get the angle

  (setq p1 (list (- (car midPoint) (* r (cos thisAngle))) (- (cadr midPoint) (* r (sin thisAngle))))) ; Compute first point
  (setq p2 (list (+ (car midPoint) (* r (cos thisAngle))) (+ (cadr midPoint) (* r (sin thisAngle))))) ; Compute second point
  (setq r (* 3.0 r))
  
  (command "PLINE" startPoint p1 "")
  (command "PLINE" (polar p1 (+ thisAngle (d2r 90)) r) (polar p1 (- thisAngle (d2r 90)) r) "")
  (command "PLINE" (polar p2 (+ thisAngle (d2r 90)) r) (polar p2 (- thisAngle (d2r 90)) r) "")
  (command "PLINE" p2 endPoint "")
  (princ)  
)

; Diode
(deFun C:E_DIODE(/ r startPoint endPoint midPoint thisAngle p1 p2)
  (setq r 1.0)
  (setq r (/ r 2.0))
  (setq startPoint (inputPoint "\n Enter the start point:")) ; Get the starting point
  (setq endPoint (inputPoint "\n Enter the end point")) ; Get the end point
  (setq midPoint (getMidPoint startPoint endPoint)) ; Calculate the middle point
  (setq thisAngle (angle startPoint endPoint)) ; Get the angle

  (setq p1 (list (- (car midPoint) (* r (cos thisAngle))) (- (cadr midPoint) (* r (sin thisAngle))))) ; Compute first point
  (setq p2 (list (+ (car midPoint) (* r (cos thisAngle))) (+ (cadr midPoint) (* r (sin thisAngle))))) ; Compute second point
  (setq r (* r 2.0))
    
  (command "PLINE" startPoint p1 "")
  (command "PLINE" (polar p1 (+ thisAngle (d2r 90)) (/ r 2.0)) (polar p1 (- thisAngle (d2r 90)) (/ r 2.0)) "")
  (command "PLINE" (polar p1 (+ thisAngle (d2r 90)) (/ r 2.0)) p2 (polar p1 (- thisAngle (d2r 90)) (/ r 2.0)) "")
  (command "PLINE" (polar p2 (+ thisAngle (d2r 90)) (/ r 2.0)) (polar p2 (- thisAngle (d2r 90)) (/ r 2.0)) "")
  (command "PLINE" p2 endPoint "")
  (princ)  
)

; Operation Amplifier
(deFun C:E_OPAMP(/ startPoint r p t1 t2 p2 p3 p4)
  (setq r 1)
  (setq startPoint (inputPoint "\n Enter v- point: "))

  (setq p (polar startPoint (d2r 0) (/ r 3.0)))
  (setq t1 (polar p (d2r 90) (/ r 3.0)))
  (setq t2 (polar t1 (d2r 270) r))

  (command "PLINE" startPoint p "") ; V-
  (command "PLINE" (polar p (d2r 0) (/ r 10.0)) (polar (polar p (d2r 0) (/ r 10.0)) (d2r 0) (/ r 6.0)) "") ; Minus
  
  (command "PLINE" t1 t2 "") ; Back
  (command "PLINE" (polar t2 (d2r 90) (/ r 3.0)) (polar (polar t2 (d2r 90) (/ r 3.0)) (d2r 180) (/ r 3.0)) "") ; V+
  (setq p3 (polar t2 (d2r 90) (/ r 3.0)))
  (command "PLINE" (polar p3 (d2r 0) (/ r 10.0)) (polar (polar p3 (d2r 0) (/ r 10.0)) (d2r 0) (/ r 6.0)) "") ; Plus Vertical
  (setq p4 (polar (polar p3 (d2r 0) (/ r 10.0)) (d2r 0) (/ r 12.0))) ; Plus Midpoint
  (command "PLINE" (polar p4 (d2r 90) (/ r 12.0)) (polar p4 (d2r 270) (/ r 12.0)) "") ; Plus Horizontal

  (setq p (polar (polar t1 (d2r 270) (/ r 2.0)) (d2r 0) r)) ; Pointy point
  (command "PLINE" t1 p t2 "") ; Triangle
  (command "PLINE" p (polar p (d2r 0) (/ r 3.0)) "") ; Output

  (setq p2 (polar (polar p (d2r 180) (/ r 2.0)) (d2r 270) (/ r 4.0)))
  (command "PLINE" p2 (polar p2 (d2r 270) (/ r 3.0)) "") ; GND

  (setq p2 (polar (polar p (d2r 180) (/ r 2.0)) (d2r 90) (/ r 4.0)))
  (command "PLINE" p2 (polar p2 (d2r 90) (/ r 3.0)) ""); VCC

  (princ)
)

; NPN bipolar transistor
(deFun C:E_NPN()(C:E_TransistorNPN))
(deFun C:E_TransistorNPN(/ startPoint p r emitter)
  (setq r 1)
  (setq startPoint (inputPoint "\n Enter v- point: "))

  (setq p (polar startPoint (d2r 0) (/ r 2.0))) ; Middle Point
  (command "PLINE" startPoint  p "") ; Base
  (command "PLINE" (polar p (d2r 90) (/ r 2.0)) (polar p (d2r 270) (/ r 2.0)) "") ; Vertical thingy
  (command "PLINE" p (polar (polar p (d2r 90) (/ r 2.0)) (d2r 0) (/ r 2.0)) "") ; Collector (NORTH)
  (command "PLINE" p (polar (polar p (d2r 270) (/ r 2.0)) (d2r 0) (/ r 2.0)) "") ; Emitter (SOUTH)
  
  (setq emitter (polar (polar p (d2r 270) (/ r 2.0)) (d2r 0) (/ r 2.0))) ; Emitter Point
  (command "PLINE" emitter "w" 0.0 (/ r 12.0) (polar emitter (d2r 135) (/ r 12.0)) "") ; Emitter Arrow
  (command "PLINE" startPoint "w" 0.0 0.0 "")
  (princ)
)

; PNP bipolar transistor
(deFun C:E_PNP()(C:E_TransistorPNP))
(deFun C:E_TransistorPNP(/ startPoint p r)
  (setq r 1)
  (setq startPoint (inputPoint "\n Enter v- point: "))

  (setq p (polar startPoint (d2r 0) (/ r 2.0))) ; Middle Point
  (command "PLINE" startPoint  p "") ; Base
  (command "PLINE" (polar p (d2r 90) (/ r 2.0)) (polar p (d2r 270) (/ r 2.0)) "") ; Vertical thingy
  (command "PLINE" p (polar (polar p (d2r 90) (/ r 2.0)) (d2r 0) (/ r 2.0)) "") ; Emitter (NORTH)
  (command "PLINE" p (polar (polar p (d2r 270) (/ r 2.0)) (d2r 0) (/ r 2.0)) "") ; Collector (SOUTH)
  (command "PLINE" p "w" 0.0 (/ r 12.0) (polar p (d2r 45) (/ r 12.0)) "") ; Emitter Arrow
  (command "PLINE" startPoint "w" 0.0 0.0 "")
  (princ)
)