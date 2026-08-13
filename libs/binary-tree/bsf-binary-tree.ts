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

function levelOrder(root: TreeNode | null): (number | null)[][] {
  if (root == null) {
    return [];
  }
  const store: (number | null)[][] = [];
  const queue: { node: TreeNode | null; level: number }[] = [
    { node: root, level: 0 },
  ];

  // use FIFO Queue
  while (queue.length > 0) {
    const { node, level } = queue.shift()!;
    if (!store[level]) {
      store[level] = [];
    }
    if (node == null) {
      store[level].push(null);
      continue;
    }
    store[level].push(node.val);
    queue.push({ node: node.left, level: level + 1 });
    queue.push({ node: node.right, level: level + 1 });
  }

  const last = store[store.length - 1];
  if (last && last.every((val) => val === null)) {
    store.pop();
  }
  return store;
}

function isSymmetric(root: TreeNode | null): boolean {
  if (root == null) {
    return false;
  }
  const store = levelOrder(root);
  return store.every((level) =>
    level.every((val, index) => val === level[level.length - 1 - index]),
  );
}

function test() {
  const n8 = new TreeNode(8);
  const n9 = new TreeNode(9);
  const n5r = new TreeNode(5);
  const n4l = new TreeNode(4);
  const n4r = new TreeNode(4, n9, n8);
  const n5l = new TreeNode(5, n8, n9);
  const n3l = new TreeNode(3, n4l, n5r);
  const n3r = new TreeNode(3, n5l, n4r);
  const n2 = new TreeNode(2, n3l, n3r);
  console.log(JSON.stringify(levelOrder(n2)));
  console.log(isSymmetric(n2));
}
test();
