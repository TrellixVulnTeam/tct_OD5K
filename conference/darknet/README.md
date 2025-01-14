## Finetune Yolov3
Finetune yolov3 training on TCT project: by the means of changing the lightness and saturation channels of images, we hope to enhance the robustness and generalization of yolov3 model.

### training
1. train1
 - _dataset_: used data batch6. Firstly, cut 1216x1216 rois and resize (cv2.pyrDown) to 608x608. Secondly, change l and s (HLS_L=[0.9], HLS_S=[0.4, 0.5]) of each image.
 - _weights_: used weights pretrained on imagenet (darknet53.conv.74).
 - _batch_: 32
 - _subdivisions_: 8
 - _learning_rate_: 0.00025
 
 - _num_classes_: 1
 - _final_steps_: 152000
 

2. train2
 - _dataset_: used data batch6. From 1216 to 608. The data contains two parts: one part is the same with train1; the other part has the same images but with original l and s.
 - _weights_: used weights trained on train1: hls09_kmeans15_152000.weights
 - _batch_: 64
 - _subdivisions_: 16
 - _learning_rate_: 0.00025
 
 - _num_classes_: 1
 - _final_steps_: 200000
 

3. train3
 - _dataset_: used data batch6. From 1216 to 608. The data contains three parts: one part is the same with train1; the other part has the same images but with original l and s; the third part rotates (90/180/270) the original images. So the dataset is five times the size of train1.
 - _weights_: used weights trained on train2: train2.backup
 - _batch_: 64
 - _subdivisions_: 16
 - _learning_rate_: 0.00025
 
 - _num_classes_: 11
 - _final_steps_: 600000


4. train4
 - _dataset_: used data batch6.1. The data is newly made: we cut positive cells and negative background images out of training wsis, and cut negative cells out of negative wsis; on negative background image, first put a random number (200~500 at most) of negative cells and then put one positive cell, with three more rotations, at random position.
 - _weights_: used weights pretrained on imagenet (darknet53.conv.74)
 - _batch_: 64
 - _subdivisions_: 16
 - _learning_rate_: 0.0005

 - _num_classes_: 11
 - _final_steps_: 100000


5. train5
 - _dataset_: used data batch6.1. The data is newly made: we cut positive cells and negative background images out of training wsis; on negative background image, we put one positive cell, with three more rotations, at random position.
 - _weights_: used weights pretrained on imagenet (darknet53.conv.74)
 - _batch_: 64
 - _subdivisions_: 16
 - _learning_rate_: 0.00025

 - _num_classes_: 11
 - _final_steps_: 100000


6. train6
 - _dataset_: used data batch6.1. The data is newly made: we cut positive cells and negative background images out of training wsis, and cut negative cells out of negative wsis; on negative background image, first put a random number (1~6 at most) of negative cells and then put one positive cell, with three more rotations, at random position.
 - _weights_: used weights pretrained on imagenet (darknet53.conv.74)
 - _batch_: 64
 - _subdivisions_: 16
 - _learning_rate_: 0.00025

 - _num_classes_: 11
 - _final_steps_: 100000


7. train7
 - _dataset_: used data batch6.2. The data is the same with train6.
 - _weights_: used weights trained in train3 (train3_600000.weights)
 - _batch_: 64
 - _subdivisions_: 16
 - _learning_rate_: 0.0001

 - _num_classes_: 11
 - _final_steps_: 680000


8. train8
 - _dataset_: used data batch6. The data is the same with train2, except that HSIL 608s are placed a 200 white bar on top, in the purpose of avoiding omitted positive cells.
 - _weights_: used weights trained in train3 (train3.backup)
 - _batch_: 64
 - _subdivisions_: 16
 - _learning_rate_: 0.0001

 - _num_classes_: 11
 - _final_steps_: 900000


9. train9
 - _dataset_: used data batch6.3, 18 classes. Newly made training data from batch6.3.
 - _weights_: used weights trained in train3 (train3.backup)
 - _batch_: 64
 - _subdivisions_: 16
 - _learning_rate_: 0.0002

 - _num_classes_: 18
 - _final_steps_: 770000


10. train10
 - _dataset_: used data batch6.3, 18 classes. Dataset contains two parts: part one is the same with train9, originally cut data; part two is part-one-highlighted, with HLS_L=[0.9], HLS_S=[0.4, 0.5].
 - _weights_: used weights trained in train9 (train9.backup)
 - _batch_: 64
 - _subdivisions_: 16
 - _learning_rate_: 0.0005

 - _num_classes_: 18
 - _final_steps_: 880000


11. train11
 - _dataset_: used data batch6.3, 13 classes. Dataset contains two parts: part one is the same with train9, originally cut data; part two is part-one-highlighted, with HLS_L=[0.9], HLS_S=[0.4, 0.5].
 - _weights_: used weights trained in train3 (train3.backup)
 - _batch_: 64
 - _subdivisions_: 16
 - _learning_rate_: 0.0002

 - _num_classes_: 13
 - _final_steps_: 850000


12. train12
 - _dataset_: used data batch6.3, 13 classes. Dataset contains two parts: part one is newly made (with some data corrections) originally cut data; part two is part-one-highlighted, with HLS_L=[0.9], HLS_S=[0.4, 0.5]. Class 1 (HSIL) data are placed a 200 bar, if plausible.
 - _weights_: used weights pretrained on imagenet (darknet53.conv.74)
 - _batch_: 64
 - _subdivisions_: 16
 - _learning_rate_: 0.00025

 - _num_classes_: 13
 - _final_steps_: 260000


13. train13
 - _dataset_: used data batch6.3, 13 classes. Dataset contains three parts: the first two parts are the same with train12; the third part is augmented (rotated) from part1 of train12. HSIL data are placed with a 200 bar.
 - _weights_: used weights trained in train12 (train12.backup)
 - _batch_: 64
 - _subdivisions_: 16
 - _learning_rate_: 0.00025

 - _num_classes_: 13
 - _final_steps_: 765000


14. train14 
 - _dataset_: used data batch6.4 (partly deleted batch6.3 and new data), 13 classes. Dataset contains three parts: part one is newly made originally cut data; part two is part-one-highlighted, with HLS_L=[0.9], HLS_S=[0.4, 0.5]; part three is augmented (rotated) from part one. HSIL data are placed with a 200 bar.
 - _weights_: used weights pretrained on imagenet (darknet53.conv.74)
 - _batch_: 64
 - _subdivisions_: 16
 - _learning_rate_: 0.00025

 - _num_classes_: 13
 - _final_steps_: 440000
 
 
15. train15 
 - _dataset_: used data batch6.4 (complete batch6.3 and new data), 13 classes. Dataset contains two parts: part one is newly made originally cut data; part two is part-one-highlighted, with HLS_L=[0.9], HLS_S=[0.4, 0.5]. HSIL data are placed with a 200 bar.
 - _weights_: used weights pretrained on imagenet (darknet53.conv.74)
 - _batch_: 64
 - _subdivisions_: 16
 - _learning_rate_: 0.00025

 - _num_classes_: 13
 - _final_steps_: 230000


16. train16 
 - _dataset_: used data batch6.4 (complete batch6.3 and new data), 13 classes. Dataset contains three parts: part one is newly made originally cut data; part two is part-one-highlighted, with HLS_L=[0.9], HLS_S=[0.4, 0.5]; part three is augmented (rotated) from part one. Autolabeled data are added.
 - _weights_: used weights pretrained on imagenet (darknet53.conv.74)
 - _batch_: 64
 - _subdivisions_: 16
 - _learning_rate_: 0.00025

 - _num_classes_: 13
 - _final_steps_: 800000
 
 
17. train17
 - _dataset_: used data batch6.4 (complete batch6.3 and new data), 13 classes. Dataset contains two parts prior to iterations 173000: part one is newly made originally cut data; part two is augmented (rotated) from part one. Autolabeled data are added. Additional data (for ASCUS/LSIL) are half-way incorporated.
 - _weights_: used weights pretrained on imagenet (darknet53.conv.74)
 - _batch_: 64
 - _subdivisions_: 16
 - _learning_rate_: 0.00025

 - _num_classes_: 13
 - _final_steps_: 900000
 
 
1. gnet1
 - _dataset_: used almost the same data as with train17, except that EC is flip augmented, autolabeled and small TRI is removed. Additional FUNGI is added on half way. Switched to g-darknet, with giou.
 - _weights_: used weights pretrained on imagenet (darknet53.conv.74)
 - _batch_: 64
 - _subdivisions_: 16
 - _learning_rate_: 0.00025

 - _num_classes_: 13
 - _final_steps_: 374048, 820000


2. gnet2
 - _dataset_: used almost the same data as with gnet1, except that HSIL/TRI data are truncated. Switched to gnet-4l.
 - _weights_: train from scratch
 - _batch_: 64
 - _subdivisions_: 16
 - _learning_rate_: 0.001

 - _num_classes_: 13
 - _final_steps_: 620000