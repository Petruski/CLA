#!/usr/bin/env python3
import subprocess 
import logging
import threading
import concurrent.futures

time_periods=[30, 60, 120]
inside_limits=[0, 0.9]
amount_of_averages=[3, 4, 5]
text_files=["Wa_Sushi.csv", "McDonalds.csv", "Big_Smajl.csv"]
#text_files=["Test.csv"]
#coordinates=[
#                [64.7501399941903, 20.959647435624287, 
#                 64.75002834051192, 20.95961613007142,
#                 64.7500520808675, 20.959212636278938, 
#                 64.75016484727189, 20.95925002902264]
#             ]
map_marker_coordinates=[
                [64.75014637790905, 20.959511013260226],
                [64.73123808474547, 20.976143250753687],
                [64.75080622400867, 20.953216106916276]
                ]
 
coordinates=[
                [64.7501399941903, 20.959647435624287, 
                 64.75002834051192, 20.95961613007142,
                 64.7500520808675, 20.959212636278938, 
                 64.75016484727189, 20.95925002902264],
                [64.73145329786514, 20.976095817820053,
                 64.73125581971021, 20.97552883947828,
                 64.73116301932735, 20.975707976807122,
                 64.73136012696044, 20.976274955148895],
                [64.75362845571969, 21.040208560499817,
                 64.75359447889826, 21.04005550184941,
                 64.75352270749454, 21.04014053443297,
                 64.75355706616904, 21.040297173402692],
                [64.75076653967135, 20.953331833312888,
                 64.75078002402496, 20.953071409705068,
                 64.75084102458827, 20.953319037933312,
                 64.75084776674734, 20.953096247794825]
            ]
def start_test(text_file, time, average, limits, cords, map_marker):
        for i_t, t in enumerate(time):
                for i_l, l in enumerate(limits):
                        for i_a, a in enumerate(average):
                                iterations = 200
                                a_low_ci = a_med_ci = a_high_ci = a_positive = a_negative = a_specificity = a_sensitivity = 0
                                a_low_ci_sda = a_med_ci_sda = a_high_ci_sda = a_positive_sda = a_negative_sda = 0
                                for x in range(iterations):
                                        child = subprocess.Popen(["/Users/macmage/Documents/CLA/cmake-build-release/CLA",
                                                str(text_file), str(l), str(t), str(a),
                                                str(map_marker[0]), str(map_marker[1]),
                                                str(cords[0]), str(cords[1]), str(cords[2]),
                                                str(cords[3]), str(cords[4]), str(cords[5]),
                                                str(cords[6]), str(cords[7])], stdout=subprocess.PIPE,
                                                stderr=subprocess.STDOUT)
                                        read_string = str(child.stdout.read())
                                        split_string = read_string[2:len(read_string)-1].split(", ")
                                        a_low_ci += float(split_string[0])
                                        a_med_ci += float(split_string[1])
                                        a_high_ci += float(split_string[2])
                                        a_low_ci_sda += float(split_string[3])
                                        a_med_ci_sda += float(split_string[4])
                                        a_high_ci_sda += float(split_string[5])
                                        a_positive += int(split_string[6])
                                        a_negative += int(split_string[7])
                                        a_positive_sda += int(split_string[8])
                                        a_negative_sda += int(split_string[9])
                                        a_specificity += float(split_string[10])
                                        a_sensitivity += float(split_string[11])

                                newline = '\n'
                                header_out = f"Text File: {text_file} | Time parameter: {t} | Number of averages: {a} | Inside limit: {l}{newline}"
                                print_out = f"Low CI Average: {(a_low_ci / iterations)} {newline}Low CI Average SDA: {(a_low_ci_sda / iterations)}{newline}Med CI Average: {(a_med_ci / iterations)} {newline}Med CI Average SDA: {(a_med_ci_sda / iterations)}{newline}High CI Average: {(a_high_ci / iterations)} {newline}High CI Average SDA: {(a_high_ci_sda / iterations)}{newline}Positive results average: {(a_positive / iterations)} {newline}Positive results average SDA: {(a_positive_sda / iterations)}{newline}Negative results average: {(a_negative / iterations)} {newline}Negative results average SDA: {(a_negative_sda /iterations)}{newline}Specificity average: {(a_specificity / iterations)} {newline}Sensitivity average: {(a_sensitivity / iterations)}{newline}"
                                print(header_out)
                                print(print_out)
                                text_file_out = text_file[0:len(text_file) - 4] + "-out.txt"
                                with open(text_file_out, "a") as o:
                                        o.write(header_out)
                                        o.write(print_out)

threads = list()
for index in range(3):
        x = threading.Thread(target=start_test, args=(text_files[index], time_periods, 
                             amount_of_averages, inside_limits, coordinates[index], map_marker_coordinates[index]))
        threads.append(x)
        x.start()
for index, thread in enumerate(threads):
        thread.join()


