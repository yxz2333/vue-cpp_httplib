<template>
    <header class="header">
        <nav>
            <h2 class="title">超市商品管理系统</h2>
        </nav>


        <img src="/src/assets/sayo.ico" class="logo" />

    </header>
</template>

<script>
export default {
    name: 'Header'
}
</script>


<style scoped>
.header {
    display: flex;
    /* 弹性盒子 */
    justify-content: space-between;
    align-items: center;
    background-color: #272424;
    color: #ffffff;
    margin: 0 0 1% 0;
}

.logo {
    width: 60px;
    height: auto;
    margin: 0 30px 0 0;
}

.title {
    margin: 0 0 0 30px;
}
</style>
