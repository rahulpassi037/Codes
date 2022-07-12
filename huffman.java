package june29;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.PriorityQueue;

public class huffman {
    public class Node implements Comparable<Node> {
        char data;
        int freq;
        Node left;
        Node right;

        @Override
        public int compareTo(Node o) {
            return this.freq - o.freq;
        }
    }

    private HashMap<Character, String> encmap = new HashMap<>();
    private HashMap<String, Character> decmap = new HashMap<>();

    public huffman(String feeder) {
        HashMap<Character, Integer> fmap = new HashMap<>();
        for(int i=0; i<feeder.length(); i++) {
            char ch = feeder.charAt(i);
            if(fmap.containsKey(ch) == false) {
                fmap.put(ch, 1);
            }
            else {
                int count = fmap.get(ch);
                count++;
                fmap.put(ch, count);
            }
        }

        PriorityQueue<Node> pq = new PriorityQueue<>();
        ArrayList<Character> keys = new ArrayList<>(fmap.keySet());
        for(Character key : keys) {
            Node add = new Node();
            add.data = key;
            add.freq = fmap.get(key);
            pq.add(add);
        }

        while(pq.size() > 1) {
            Node one = pq.remove();
            Node two = pq.remove();
            Node merged = new Node();
            merged.freq = one.freq + two.freq;
            merged.left = one;
            merged.right = two;
            pq.add(merged);
        }
        Node root = pq.remove();
        transverse(root, "");
    }

    private void transverse(Node node, String asf) {
        if(node.left == null && node.right == null) {
            encmap.put(node.data, asf);
            decmap.put(asf, node.data);
            return;
        }
        transverse(node.left, asf + "0");
        transverse(node.right, asf + "1");
    }
    
    public String encode(String str) {
        String ans = new String();
        for(int i=0; i<str.length(); i++) {
            char ch = str.charAt(i);
            String get = encmap.get(ch);
            ans += get;
        }
        return ans;
    }

    public String decode(String str) {
        int i = 0;
        String st = "";
        String ans = "";
        while(i < str.length()) {
            char ch = str.charAt(i);
            st += ch;
            if(decmap.containsKey(st) == true) {
                ans += decmap.get(st);
                st = "";
            }
            i++;
        }
        return ans;
    }
}
