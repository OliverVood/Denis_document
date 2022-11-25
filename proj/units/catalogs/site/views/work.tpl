<?php

	namespace Proj\Site\Templates\Catalogs;

	use Base\Templates\View;

	class Work extends View {

		public function ToVar(): string {
			$this->Start();
			$this->Render();
			return $this->Read();
		}

		public function Render() { ?>
			<div class = "view catalogs work">
				<div class = "btns tabu">
					<input type = "button" value = "+ Добавить таблицу" onclick = "Estimate.AddList();"><input type = "button" value = "p Печать" onclick = "window.print();">
				</div>
				<div class = "container"></div>
				<script>
					let Estimate = new Site.Catalogs.Estimate('.view.catalogs.work > .container');
				</script>
			</div>
		<?php }

	}