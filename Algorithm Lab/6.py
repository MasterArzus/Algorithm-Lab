import sys
import random
from time import *

from PyQt5.QtWidgets import *
from PyQt5 import uic


def checkdone(list):
    correct = 0
    for i in range(0, 8):
        if list[i] == i + 1:
            correct += 1
    return correct


class MyWindow(QWidget):
    def __init__(self):
        super().__init__()
        self.BABlist = []
        self.laststep = None
        self.boolbestfs = False
        self.boolbfs = False
        self.step = None
        self.time = None
        self.algorithm = 0
        self.p = None
        self.p9 = None
        self.p8 = None
        self.p7 = None
        self.p6 = None
        self.p5 = None
        self.p4 = None
        self.p3 = None
        self.p1 = None
        self.p2 = None
        self.eight = [1, 2, 3, 4, 5, 6, -1, 7, 8]
        self.ans = None
        self.rbtn_BAB = None
        self.rbtn_BestFS = None
        self.rbtn_DFS = None
        self.btn_run = None
        self.rbtn_BFS = None
        self.ui = None
        self.btn_init = None
        self.steps = 0
        self.level = 0
        self.exchange = [[3, 1], [4, 2, 0], [5, 1], [6, 4, 0], [7, 5, 3, 1], [8, 4, 2], [7, 3], [4, 6, 8], [5, 7]]
        self.init_ui()

    def init_ui(self):
        self.ui = uic.loadUi("./8_Puzzle.ui")
        # print(self.ui.__dict__)
        self.btn_init = self.ui.Button_Init
        self.btn_init.clicked.connect(self.init)
        self.btn_run = self.ui.Button_run
        self.btn_run.clicked.connect(self.Run)
        self.rbtn_BFS = self.ui.RButton_BFS
        self.rbtn_BFS.clicked.connect(self.check)
        self.rbtn_DFS = self.ui.RButton_DFS
        self.rbtn_DFS.clicked.connect(self.check)
        self.rbtn_BestFS = self.ui.RButton_BestFS
        self.rbtn_BestFS.clicked.connect(self.check)
        self.rbtn_BAB = self.ui.RButton_BAB
        self.rbtn_BAB.clicked.connect(self.check)
        self.p = []
        self.p.append(self.ui.Button_p1)
        self.p.append(self.ui.Button_p2)
        self.p.append(self.ui.Button_p3)
        self.p.append(self.ui.Button_p4)
        self.p.append(self.ui.Button_p5)
        self.p.append(self.ui.Button_p6)
        self.p.append(self.ui.Button_p7)
        self.p.append(self.ui.Button_p8)
        self.p.append(self.ui.Button_p9)
        self.time = self.ui.label_2
        self.step = self.ui.label_3
        self.setp()

    def init(self):
        random.shuffle(self.eight)  # list重排
        print(self.eight)
        self.setp()

    def setp(self):
        for i in range(0, 9):
            if self.eight[i] == -1:
                self.p[i].setText('')
            else:
                self.p[i].setText(str(self.eight[i]))

    def check(self):
        if self.rbtn_BFS.isChecked():
            self.algorithm = 1
        elif self.rbtn_DFS.isChecked():
            self.algorithm = 2
        elif self.rbtn_BestFS.isChecked():
            self.algorithm = 3
        elif self.rbtn_BAB.isChecked():
            self.algorithm = 4
        else:
            self.algorithm = 0

    def Run(self):
        self.steps = 0
        self.level = 0

        if self.algorithm == 0:
            self.time.setText('Should chose one algorithm first')
        elif self.algorithm == 1:
            self.boolbfs = False
            st = time()
            BFSsteps = self.BFS(self.eight,-1)
            ed = time()
            if self.steps == 1501:
                self.time.setText("can't find the answer in 1500 steps")
                self.step.setText("Steps : 1500")
                self.eight = self.ans
                self.setp()
            else:
                self.eight = [1, 2, 3, 4, 5, 6, 7, 8, -1]
                print(BFSsteps)
                print(self.eight)
                self.time.setText("BFS total time(s) : " + str(ed - st))
                self.step.setText("BFS total steps : " + str(self.steps))
                self.setp()
        elif self.algorithm == 2:
            st = time()
            DFSsteps = self.DFS(self.eight,-1)
            ed = time()
            if DFSsteps == 0:
                self.time.setText("can't find the answer in 1500 steps")
                self.step.setText("Steps : 1500")
                self.setp()
            else:
                # print(DFSsteps)
                self.time.setText("DFS total time(s) : " + str(ed - st))
                self.step.setText("DFS total steps : " + str(self.steps))
                self.setp()
        elif self.algorithm == 3:
            self.boolbestfs = False
            st = time()
            BestFSsteps = self.BestFS(self.eight,-1)
            ed = time()
            if self.steps == 1501:
                self.time.setText("can't find the answer in 1500 steps")
                self.step.setText("Steps : 1500")
                self.setp()
            else:
                self.eight = [1, 2, 3, 4, 5, 6, 7, 8, -1]
                print(BestFSsteps)
                print(self.eight)
                self.time.setText("BestFS total time(s) : " + str(ed - st))
                self.step.setText("BestFS total steps : " + str(self.steps))
                self.setp()
        elif self.algorithm == 4:
            st = time()
            self.BABlist.clear()
            for i in self.eight:
                self.BABlist.append(i)
            BestFSsteps = self.BestFS(self.eight, -1)
            step = self.steps
            print(BestFSsteps)
            self.steps=0
            BABsteps = self.BAB(self.BABlist,-1,step)
            ed = time()
            if self.steps == 1502:
                self.time.setText("can't find the answer in 1500 steps")
                self.step.setText("Steps : 1500")
                self.setp()
            else:
                self.eight = [1, 2, 3, 4, 5, 6, 7, 8, -1]
                print(BestFSsteps)
                print(self.BABlist)
                self.time.setText("BAB total time(s) : " + str(ed - st))
                self.step.setText("BAB total steps : " + str(self.steps))
                self.setp()

    def DFS(self, list,last):  # list[1,2,3,4,5,6,7,8,9]
        # print("level:" + str(self.level))
        self.steps += 1
        print(self.steps)
        thislist = []
        for i in range(0, 9):
            thislist.append(list[i])
        print(thislist)
        if self.steps > 1500:
            self.eight = thislist
            print(self.eight)
            self.level -= 1
            return 0
        if checkdone(thislist) == 8:
            self.eight = thislist
            print(self.eight)
            print('found!')
            return self.steps
        empty = thislist.index(-1)
        random.shuffle(self.exchange)
        self.level += 1
        for i in self.exchange[empty]:
            if not i == last:
                thislist1 = []
                for j in range(0,9):
                    thislist1.append(thislist[j])
                thislist1[empty] = thislist[i]
                thislist1[i] = -1
                if checkdone(thislist1) == 8:
                    print("found!")
                    self.eight = thislist1
                    print(self.eight)
                    self.setp()
                    return self.steps
                else:
                    if self.level >= 50:
                        self.level -= 2
                        continue
                    else:
                        return self.DFS(thislist1,i)
        self.level -= 2
        self.eight = thislist



    def BFS(self, list,last):  # list[1,2,3,4,5,6,7,8,9]
        # print("level:" + str(self.level))
        if not self.boolbfs:
            self.steps += 1
            print(self.steps)
            thislist = []
            for i in range(0, 9):
                thislist.append(list[i])
            print(thislist)
            if self.steps > 1500:
                # self.eight = list
                self.ans = list
                print(self.eight)
                self.boolbfs = True
                return 0
            if checkdone(thislist) == 8:
                self.eight = thislist
                print(self.eight)
                print('found!')
                self.boolbfs = True
                return self.steps
            else:
                empty = thislist.index(-1)
                random.shuffle(self.exchange)
                for i in self.exchange[empty]:
                    if not i == last:
                        thislist1=[]
                        for j in range(0,9):
                            thislist1.append(thislist[j])
                        thislist1[empty] = thislist[i]
                        thislist1[i] = -1
                        if checkdone(thislist1) == 8:
                            print("found!")
                            self.eight = thislist1
                            print(self.eight)
                            self.setp()
                            self.boolbfs = True
                            break
                        else:
                            continue
                if not self.boolbfs:
                    for i in self.exchange[empty]:
                        if not i == last:
                            thislist2 = []
                            for j in range(0, 9):
                                thislist2.append(thislist[j])
                            thislist2[empty] = thislist[i]
                            thislist2[i] = -1
                            return self.BFS(thislist2,i)
                    self.eight = thislist
        else:
            return self.steps

    def BestFS(self,list,last):
        if not self.boolbestfs:
            best = []
            self.steps += 1
            print(self.steps)
            thislist = []
            for i in range(0, 9):
                thislist.append(list[i])
            print(thislist)
            if self.steps > 1500:
                self.eight = list
                print(self.eight)
                self.boolbestfs = True
                return 0

            if checkdone(thislist) == 8:
                self.eight = thislist
                print(self.eight)
                print('found!')
                self.boolbestfs = True
                return self.steps
            else:
                empty = thislist.index(-1)
                random.shuffle(self.exchange)
                for i in self.exchange[empty]:
                    if not i == last:
                        thislist1 = []
                        for j in range(0, 9):
                            thislist1.append(thislist[j])
                        thislist1[empty] = thislist[i]
                        thislist1[i] = -1
                        best.append([checkdone(thislist),i])
                        if checkdone(thislist1) == 8:
                            print("found!")
                            self.eight = thislist1
                            print(self.eight)
                            self.setp()
                            self.boolbestfs = True
                            return self.steps
                        else:
                            continue
                if not self.boolbestfs:
                    exch = sorted(best,key=(lambda x:x[0]),reverse=True)
                    print(exch)

                    for i in exch:
                        if not i[1] == last:
                            thislist2 = []
                            for j in range(0, 9):
                                thislist2.append(thislist[j])
                            thislist2[empty] = thislist[i[1]]
                            thislist2[i[1]] = -1
                            return self.BestFS(thislist2,i[1])
                    self.eight = thislist
        # else:
        #     return self.steps
    def BAB(self,list,last,step):
        # print("level:" + str(self.level))
        self.steps += 1
        print(self.steps)
        thislist = []
        for i in range(0, 9):
            thislist.append(list[i])
        print(thislist)
        if self.steps > 1500:
            self.eight = thislist
            print(self.eight)
            self.level -= 1
            return 0
        if checkdone(thislist) == 8:
            self.eight = thislist
            print(self.eight)
            print('found!')
            return self.steps
        empty = thislist.index(-1)
        random.shuffle(self.exchange)
        self.level += 1
        if step > self.steps:
            for i in self.exchange[empty]:
                if not i == last:
                    thislist1 = []
                    for j in range(0, 9):
                        thislist1.append(thislist[j])
                    thislist1[empty] = thislist[i]
                    thislist1[i] = -1
                    if checkdone(thislist1) == 8:
                        print("found!")
                        self.eight = thislist1
                        print(self.eight)
                        self.setp()
                        return self.steps
                    else:
                        if self.level >= 50:
                            self.level -= 2
                            continue
                        else:
                            return self.DFS(thislist1, i)
        else:
            return 0
        self.level -= 2
        self.eight = thislist







# testlist = [1,2,3,4,5,6,7,-1,8]
# BFS(testlist)

if __name__ == '__main__':
    sys.setrecursionlimit(5000)
    app = QApplication(sys.argv)
    w = MyWindow()
    w.ui.show()
    sys.exit(app.exec_())

