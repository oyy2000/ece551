bfs(from, to)
{
    Queue todo;
    // only change Stack -> Queue
    Set visited;
    limitedColor = from.color;
    todo.push(the path[from]);
    as long as todo is not empty
    {
        currentPath = todo.pop();
        currentNode = currentPath.lastNode();
        if (currentNode == to)
        {
            return currentPath
        }
    }
    if (currentNode is not in visited)
    {
        visited.add(currentNode);
        for each (x adjacent to currentNode and the color of x is same as limitedColor)
        {
            todo.push(currentPath.addNode(x));
        }
    }
    return the empty path
}
