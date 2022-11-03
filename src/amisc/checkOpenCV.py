import cv2

arr = []
while index <100:
    cap = cv2.VideoCapture(index,cv2.CAP_XIAPI)
    if cap.read()[0]:
        arr.append(index)
    cap.release()
    index += 1
print(arr)
index = 0
arr = []
while index <100:
    cap = cv2.VideoCapture(index,cv2.CAP_V4L)
    if cap.read()[0]:
        arr.append(index)
    cap.release()
    index += 1
print(arr)

# cap = cv2.VideoCapture(0,cv2.CAP_XIAPI)
# while True:
#     ret, frame = cap.read()
#     cv2.imshow("frame",frame)
#     if cv2.waitKey(1) == ord('q'):
#         break
# cap.release()
# cv2.destroyAllWindows()

# # print(cv2.getBuildInformation())