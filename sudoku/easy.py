from numpy import array

array([[0 for _ in range(9)] for _ in range(9)])

matrix = (
array([[0, 4, 1, 0, 0, 0, 7, 3, 0],
       [8, 0, 5, 0, 0, 1, 0, 0, 4],
       [7, 0, 0, 0, 4, 0, 0, 1, 2],
       [0, 1, 0, 0, 8, 0, 0, 0, 0],
       [0, 0, 7, 5, 0, 9, 8, 0, 0],
       [0, 0, 0, 0, 1, 0, 0, 7, 0],
       [5, 3, 0, 0, 2, 0, 0, 0, 6],
       [1, 0, 0, 4, 0, 0, 2, 0, 7],
       [0, 7, 9, 0, 0, 0, 1, 4, 0]])
)

width = 9
height = 9
width_mini = int(width ** 0.5)
height_mini = int(height ** 0.5)

row = [{i for i in range(1, width + 1)} for _ in range(height)]
column = [{i for i in range(1, height + 1)} for _ in range(width)]
mini = [{i for i in range(1, (width_mini * height_mini) + 1)} for  _ in range((width // width_mini) * (height // height_mini))]

not_done = {i for i in range(width * height)}

while not_done:
    element = not_done.pop()
    if matrix[element // width][element % width] == 0:
        solutions = row[element // width] & column[element % width] & mini[(element // width // height_mini) * width_mini + (element % width) // width_mini]
        if len(solutions) == 1:
            solution = solutions.pop()
            matrix[element // width][element % width] = solution
            row[element // width].remove(solution)
            column[element % width].remove(solution)
            mini[(element // width // height_mini) * width_mini + (element % width) // width_mini].remove(solution)
        else:
            not_done.add(element)
    else:
        solution = matrix[element // width][element % width]
        row[element // width].remove(solution)
        column[element % width].remove(solution)
        mini[(element // width // height_mini) * width_mini + (element % width) // width_mini].remove(solution)

print(array(matrix))
