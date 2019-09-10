import { Layout } from 'antd';

import styles from './styles.css';

const { Footer } = Layout;

export default function({ location }) {
  return (
    <Footer className={styles.footer}>
      Ryan Luu &#169; 2019
    </Footer>
  );
};
