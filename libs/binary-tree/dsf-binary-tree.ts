class TreeNode {
  val: number;
  left: TreeNode | null;
  right: TreeNode | null;
  constructor(val?: number, left?: TreeNode | null, right?: TreeNode | null) {
    this.val = val === undefined ? 0 : val;
    this.left = left === undefined ? null : left;
    this.right = right === undefined ? null : right;
  }
}

function inorderTraversal(root: TreeNode | null): number[] {
  if (root === null) {
    return [];
  }
  if (root.left === null && root.right === null) {
    return [root.val];
  }

  const store: (number | null)[] = [];
  const realS: (number | null)[] = [];
  function traverse(root: TreeNode | null, store: (number | null)[]) {
    // dept search LIFO
    if (root === null) {
      const a = store.pop();
      if (a !== undefined) {
        realS.push(a);
      }
      return;
    }
    store.push(root.val);

    traverse(root.left, store);
    traverse(root.right, store);
  }
  traverse(root, store);
  return realS.filter((v) => v != null);
}

function test() {
  const root = new TreeNode(1);
  root.left = new TreeNode(2);
  root.right = new TreeNode(3);
  root.left.left = new TreeNode(4);
  root.left.right = new TreeNode(5);
  root.left.right.left = new TreeNode(6);
  root.left.right.right = new TreeNode(7);
  root.right.right = new TreeNode(8);
  root.right.right.left = new TreeNode(9);
  inorderTraversal(root);
}

function test2() {
  const root = new TreeNode(1);
  root.right = new TreeNode(2);
  root.right.left = new TreeNode(3);
  inorderTraversal(root);
}

test();
test2();
