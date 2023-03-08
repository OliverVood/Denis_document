<?php

	namespace Proj\Site\Templates\Catalogs;

	use Base\Templates\View;

	class PriceList extends View {

		public function ToVar(): string {
			$this->Start();
			$this->Render();
			return $this->Read();
		}

		public function Render(): void { ?>
			<div class = "view catalogs work">
				<h1 class = "glob_print_tabu">Работа с прайс-листами</h1>
				<script>
					let PriceList = new Site.Catalogs.PriceListController('.view.catalogs.work');
				</script>
			</div>
		<?php }

	}