package halfbyte.game.tprg.battle;

import com.badlogic.gdx.math.GridPoint2;
import java.util.HashSet;
import java.util.LinkedList;
import java.util.Queue;
import java.util.Set;
import halfbyte.game.tprg.Utils;

public class Pathfinder {
    public static class Node{
        public GridPoint2 point;
        public int cost;

        public Node(GridPoint2 point, int cost){
            this.point = point;
            this.cost = cost;
        }

        @Override
        public boolean equals(Object obj) {
            if (obj instanceof Node){
                Node other = (Node) obj;
                if (this.point.x == other.point.x && this.point.y == other.point.y){
                    return true;
                }
            }
            return false;
        }
    }

    // variables
    private int m_width;
    private int m_height;
    private Node m_nodes[][];


    // methods
    public Pathfinder(int width, int height){
        this.m_width = width;
        this.m_height = height;
        this.m_nodes = new Node[this.m_width][this.m_height];
        for (int y = 0; y < this.m_height; ++y){
            for (int x = 0; x < this.m_width; ++x){
                this.m_nodes[x][y] = new Node(new GridPoint2(x, y), -1);
            }
        }
    }

    public Set<Node> computeWalkable(Battle battle, Entity entity, int startX, int startY, int distance){
        // reset the nodes cost
        for (int y = 0; y < this.m_height; ++y){
            for (int x = 0; x < this.m_width; ++x){
                this.m_nodes[x][y].cost = 9999999;
            }
        }

        // frontier
        Queue<Node> frontier = new LinkedList<>();

        // walkable list
        Set<Node> walkable = new HashSet<>();

        // cost of start
        this.m_nodes[startX][startY].cost = 0;

        // add start to frontier
        frontier.add(this.m_nodes[startX][startY]);

        // add start to walkable
        walkable.add(this.m_nodes[startX][startY]);

        // loop while frontier not empty
        while (frontier.isEmpty() == false){
            // get the lead item
            Node node = frontier.poll();

            // check if it is max distance
            if (node.cost < distance){
                // iterate directions
                for (GridPoint2 dir : Utils.CARDINAL_DIRECTIONS){
                    // compute point
                    int px = node.point.x + dir.x;
                    int py = node.point.y + dir.y;

                    // make sure valid and walkable
                    if (this.isValidPoint(px, py) && battle.getIsTileWalkable(entity, px, py)) {
                        // get handle to the neighbor
                        Node neighbor = this.m_nodes[px][py];

                        // check if already in walkable
                        if (walkable.contains(neighbor) == false) {
                            // update cost
                            neighbor.cost = node.cost + 1;

                            // add to frontier
                            frontier.add(neighbor);

                            // put in walkable
                            walkable.add(neighbor);
                        }
                    }
                }
            }
        }

        // done
        return walkable;
    }

    private boolean isValidPoint(int x, int y){
        if (x < 0 || x > this.m_width - 1 || y < 0 || y > this.m_height - 1){
            return false;
        }
        return true;
    }
}
