class Node
{
    int val;
    Node next;

    Node(int data)
    {
        this.val = data;
        this.next = null;
    }

    static void printList(Node head)
    {
        System.out.print("List data : ");
        while(head != null)
        {
            System.out.print(head.val + " ");
            head = head.next;
        }
        System.out.println();
    }
}

class TreeNode
{
    int data;
    TreeNode left, right;

    TreeNode(int val)
    {
        this.data = val;
        this.left = null;
        this.right = null;
    }

    static void inorder(TreeNode root)
    {
        if(root == null) return;

        inorder(root.left);
        System.out.print(root.data + " ");
        inorder(root.right);
    }
}

class test
{
    public static void main(String[] args)
    {
        Node head = new Node(0);

        head.next = new Node(1);
        head.next.next = new Node(2);
        head.next.next.next = new Node(3);
        head.next.next.next.next = new Node(4);
        head.next.next.next.next.next = new Node(5);

        Node.printList(head);
        Node.printList(head);

        TreeNode root = new TreeNode(0);
        root.left = new TreeNode(1);
        root.left.left = new TreeNode(2);
        root.left.right = new TreeNode(3);
        root.right = new TreeNode(4);

        System.out.print("Inorder Traversal of List : ");
        TreeNode.inorder(root);
        System.out.println();
    }
}