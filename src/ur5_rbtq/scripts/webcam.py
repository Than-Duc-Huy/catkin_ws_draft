import cv2

cam = cv2.VideoCapture(0,cv2.CAP_V4L2)

while True:
    ret,frame = cam.read()
    cv2.imshow("output",frame)
    if cv2.waitKey(1) == ord('q'):
        break
cv2.destroyAllWindows()
cam.close