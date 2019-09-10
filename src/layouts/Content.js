import { Layout, Breadcrumb } from 'antd';

import styles from './styles.css';

const { Content } = Layout;

export default function({ children, location }) {
  let breadcrumbs = [];
  let tokens = location.pathname.split('/');
  tokens[0] = 'home';
  for (let index in tokens) {
    let token = tokens[index].charAt(0).toUpperCase() + tokens[index].slice(1);
    breadcrumbs.push(<Breadcrumb.Item key={index}>{token}</Breadcrumb.Item>);
  }

  return (
    <Content className={styles.content}>
      <Breadcrumb style={{'margin': '16px 0'}}>
        {breadcrumbs}
      </Breadcrumb>
      <div className={styles.main}>
        {children}
      </div>
    </Content>
  );
};
