extern crate image;
use image::ImageBuffer;

type Utype = usize;

use std::f64;
//use std::cmp::{min, max};
use rand::{Rng, SeedableRng};
use rand_xoshiro::Xoshiro256StarStar;

const PI: f64 = f64::consts::PI;
const R1: f64 = 20.0;
const R2: f64 = 24.0;   // R2 > R1
// const SIG0: f64 = 0.0;
// const SIG1: f64 = 1.0;
// const SIGINF: f64 = 10_000.0;
const RES: f64 = 1.0;
//const PHI: f64 = PI / 2.0;

//格点
#[derive(Debug, Clone)]
struct Site {
    site: Option<Vec<Utype>>,
}

//二维网格
struct Graph {
    x_length: usize,
    y_length: usize,
    graph: Vec<Vec<Site>>,
}

#[allow(dead_code)]
impl Site {
    //! 为单个格点实现方法
    //! true  -> 1
    //! false -> 0
    fn new() -> Site {
        Site { site: Option::None }
    }

    //增加标号
    fn mark(&mut self, num: Utype) {
        if let Some(ref mut vec1) = self.site {
            //有则退出，无则添加
            for elem in &vec1[..] {
                if *elem == num {
                    return;
                }
            }
            vec1.push(num);
        } else {
            let vec1 = vec![num];
            self.site = Some(vec1);
        }
    }

    //增加多个标号，之后递增排序
    fn add(&mut self, set: &[Utype]) {
        for i in set {
            self.mark(*i);
        }
        if let Some(ref mut vec1) = self.site {
            vec1.sort_unstable();
        }
    }

    //清除site，变为未占据态
    fn erase(&mut self) {
        self.site = None;
    }

    //判断是否被占据
    fn is_sited(&self) -> bool {
        self.site.is_some()
    }

    //引用跟随
    fn check(&self) -> &Option<Vec<Utype>> {
        &self.site
    }

    //判断某序号是否在格点上,默认self中vec已升序排列
    fn has(&self, num: Utype) -> bool {
        if let Some(ref vec1) = self.site {
            for p in vec1 {
                if *p > num {
                    return false;
                }
                if *p == num {
                    return true;
                }
            }
            false
        } else {
            false
        }
    }
}

#[allow(dead_code)]
impl Graph {
    //新建二维网格，全部为未占据态
    fn new(x_length: usize, y_length: usize) -> Graph {
        Graph {
            x_length,
            y_length,
            //Graph[y][x], Graph[0][0]<-->upperleft
            graph: vec![vec![Site::new(); x_length]; y_length],
        }
    }

    //画一个图形，其标号为n
    fn put_one<T: Rng>(&mut self, rng: &mut T, n: Utype) {
        let (x0, y0, theta, phi) = rng.gen::<(f64, f64, f64, f64)>();
        let x0 = x0 * (self.x_length as f64 + 2.0 * R2) - R2;
        let y0 = y0 * (self.y_length as f64 + 2.0 * R2) - R2;
        let theta = (2.0 * theta - 1.0) * PI;
        let phi = (7.0/8.0 * phi + 1.0/16.0)* PI ;
        //确定扫描范围，防止越界。
        let ya = f64::max((y0 - R2).floor(), 0.0) as usize;
        let xa = f64::max((x0 - R2).floor(), 0.0) as usize;
        let yb = f64::min((y0 + R2).ceil(), self.y_length as f64 - 1.0) as usize;
        let xb = f64::min((x0 + R2).ceil(), self.x_length as f64 - 1.0) as usize;
        for i in ya..=yb {
            for j in xa..=xb {
                let x = j as f64 - x0;
                let y = i as f64 - y0;
                if modpi(f64::atan2(y, x), theta) <= phi {
                    let r2 = x * x + y * y;
                    if r2 > R1 * R1 && r2 <= R2 * R2 {
                        self.graph[i][j].add(&[n]);
                    }
                }
            }
        }
    }

    //合并连通集团，给出集团序号对照表
    fn find_way(&mut self, n: Utype) -> Vec<Utype> {

        //对应倒数第二行/列
        let xd = self.x_length - 2;
        let yd = self.y_length - 2;

        //初始化上下边界
        for i in 0..self.x_length {
            self.graph[0][i].mark(1);
            self.graph[1][i].mark(1);
            self.graph[yd][i].mark(2);
            self.graph[yd + 1][i].mark(2);
        }

        //截断左右边界
        for j in 1..=yd {
            self.graph[j][0].erase();
            self.graph[j][xd + 1].erase();
        }

        //集合vec，连通的序号属于一个集合，不同集合中的序号不连通
        let mut setvec: Vec<Site> = {
            //定义前两个集合分别为与上边界连通的1，与下边界联通的2.
            let mut _s1 = Site::new();
            let mut _s2 = Site::new();
            _s1.mark(1);
            _s2.mark(2);
            vec![_s1, _s2]
        };

        for y in 1..=yd {
            'outer: for x in 1..=xd {
                //若该点被占据，收集该点与左、上相邻两点所含的序号的集合，记为set
                if let Some(local) = self.graph[y][x].check() {
                    let mut set = Site::new();
                    set.add(&local);
                    //左侧有占据点，将左侧所含数字加入集合
                    if let Some(tmp) = self.graph[y][x - 1].check() {
                        set.add(&tmp);
                    }
                    //上方有占据点，同理
                    if let Some(tmp) = self.graph[y - 1][x].check() {
                        set.add(&tmp);
                    }
                    //set<-set.unwrap
                    if let Some(set) = set.site {
                        if set.len() == 1 {
                            continue 'outer;
                        }
                        for pnum in &set {
                            'inner: for tmpset in &mut setvec {
                                //若set中含有已合并过的序号
                                if tmpset.has(*pnum) {
                                    //将set合并入当前集合
                                    tmpset.add(&set);
                                    self.graph[y][x] = Site::new();
                                    //用最小序号代表所有其他序号
                                    self.graph[y][x].mark(set[0]);
                                    continue 'outer;
                                } else {
                                    //检查下一个
                                    continue 'inner;
                                }
                            }
                        }
                        setvec.push(Site {
                            site: Some(set),
                        });
                    }
                } //end if
            }
        }

        //合并集团
        let length = setvec.len();
        let mut _flag;
        loop {
            _flag = false;
            'outer2: for i in 0..length {
                'inner2: for j in (i + 1)..length {
                    //若不为空，检查与之前集合是否有交集
                    if let Some(set2) = setvec[j].site.clone() {
                        let set1 = &mut setvec[i];
                        if !set1.is_sited() {
                            continue 'outer2;
                        }
                        for pnum in &set2 {
                            //若有交集则合并集合
                            if set1.has(*pnum) {
                                set1.add(&set2);
                                setvec[j] = Site::new();
                                _flag = true;
                                continue 'inner2;
                            }
                        }
                        
                    }
                }
            }

            if !_flag {
                //本次循环后无任何修改操作，则说明已完全合并，退出循环
                break;
            }
        }

        let mut bvec: Vec<Utype> = Vec::with_capacity(n + 1);
        for i in 0..=n {
            bvec.push(i);
        }
        for set in &setvec {
            if let Some(tvec) = set.check() {
                for p in tvec {
                    //用集团中最小编号代表集团
                    bvec[*p] = tvec[0];
                }
            }
        }
        
        for y in 1..=yd {
            for x in 1..= xd {
                if let Some(ref mut vec) = self.graph[y][x].site {
                    //最小化编号
                    vec[0] = bvec[vec[0]];
                }
            }
        }
        
        //返回对照表
        bvec
    }

    fn get_pc(&self) -> f64 {
        let mut count = 0_u64;
        for i in 0..self.y_length {
            for j in 0..self.x_length {
                if self.graph[i][j].site.is_some() {
                    count += 1;
                }
            }
        }
        count as f64/self.x_length as f64/self.y_length as f64
    }

    //删除所有非连通格点
    fn pure(&mut self) {
        for i in 0..self.y_length {
            for j in 0..self.x_length {
                if let Some(ref vec) = self.graph[i][j].site {
                    //标记不为1，说明不与上边界连通
                    if vec[0] != 1 {
                        self.graph[i][j].erase();
                    }
                }
            }
        }
    }

    fn get_condt(&self) -> f64 {
        let n = self.y_length - 3;
        let xd = self.x_length - 2;
        //其中矩阵A的0和n+1行、列为冗余项，仅为保证代码一致性
        let mut A = vec![vec![0_f64;n+2];n+2];
        for i in 0..n {
            A[i][i] = 1.0;
        }
        for l in 1..=xd {
            for r in 2..=n {
                //横向bind
                if self.graph[r][l].is_sited() && self.graph[r][l-1].is_sited() {
                    let B = A.clone();
                    for i in 1..=n {
                        for j in 1..=n {
                            A[i][j] = B[i][j] - B[i][r]*B[r][j]/(1.0/RES+B[r][r]);
                        }
                    }
                }
            }
            for r in 1..=n {
                //纵向bind
                if self.graph[r][l].is_sited() && self.graph[r+1][l].is_sited() {
                    A[r][r] += 1.0/RES;
                    A[r][r+1] += -1.0/RES;
                    A[r+1][r] += -1.0/RES;
                    A[r+1][r+1] += 1.0/RES;
                }
            }
        }
        A[1][1]
    }

}

//给定两角度[-pi,pi]，求出二者之差，[0,pi]
fn modpi(theta1: f64, theta2: f64) -> f64 {
    let a: f64 = (theta1 - theta2).abs();
    if a <= PI {
        a
    } else {
        2.0 * PI - a
    }
}

//*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*

fn main() {
    let x: u32 = 500;
    let y: u32 = 500;
    let total = 1;     //每种pc统计次数
    let mut g: Graph;   //二维网格
    let lmax = 3;
    let mut pvec: Vec<(f64,f64,f64)> = Vec::with_capacity(lmax+1);
    let mut rng = Xoshiro256StarStar::seed_from_u64((total*x) as u64);

    for l in 0..=lmax {
        /* 
        let mut sigma = 0_f64;
        */
        let mut pc = 0_f64;
        let mut succeed = 0;
       
        let end: usize = 400 + l*10;
        for count in 1..=total {

            //print!("main_1\ngenerating lattice... ");
            g = Graph::new(x as usize, y as usize);
            //println!("done");

            //println!("puting circles on the lattice... ");
            for i in 3..end {
                g.put_one(&mut rng, i as Utype);
            }
            // println!("done");

            // println!("calculating...");
            let bvec = g.find_way(end as Utype);
            //绘图
            if false {
                println!("finished calculating, now drawing...");
                let img1 = ImageBuffer::from_fn(x, y, |a, b| {
                    let site = &g.graph[b as usize][a as usize];
                    if let Some(vec1) = site.check() {
                        match bvec[vec1[0]] {
                            1 => image::Rgb([0xFF, 0x00, 0x33]), //red
                            2 => image::Rgb([0x00, 0x33, 0xFF]), //blue
                            _ => image::Rgb([0x66, 0x33, 0x33]),
                        }
                    } else {
                        //白背景
                        image::Rgb([0xFF, 0xFF, 0xFF])
                    }
                });
                img1.save("./img/img_".to_string() + &l.to_string() + "_" + &count.to_string() + ".jpg").unwrap();
            }
            
            pc += g.get_pc();  
            //检查上下边界是否连通
            if let Some(vec) = g.graph[y as usize - 2][1].check() {
                if bvec[vec[0]] == 1 {
                    succeed += 1;
                    /*g.pure();
                    sigma += g.get_condt();*/
                } else {
                    succeed += 0;
                    //sigma += 0.0; //表示不导通时，电导率按0计算
                }
            }
            // println!("finished {}\n", count);

        }
        
        let _pc = pc/total as f64;
        let _pt = succeed as f64 / total as f64;
        //单位正方形上下电导值
        let _sig = end as f64;//sigma * y as f64 / x as f64 / total as f64;
        println!("pc = {:.4}, Probability: {:.4}\n", _pc, _pt);
        // println!("******************************\n");
        pvec.push((_pc, _pt, _sig));
        
    }
    
    print!("N={}\t(R1, R2)={:?}\n pc\tp\n", x, (R1, R2));
    for (pc, p, _l) in pvec {
        print!("{:.4}\t{:.4}\t{}\n", pc, p, _l);
    }
    
    println!("all finished!\n");
}
