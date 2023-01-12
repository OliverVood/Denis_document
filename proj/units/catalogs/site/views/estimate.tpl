<?php

	namespace Proj\Site\Templates\Catalogs;

	use Base\Templates\View;

	class Estimate extends View {

		public function ToVar(): string {
			$this->Start();
			$this->Render();
			return $this->Read();
		}

		public function Render() { ?>
			<div class = "view catalogs work">
				<h1 class = "glob_print_tabu">Работа со сметами</h1>
				<script>
					let Estimate = new Site.Catalogs.EstimateController('.view.catalogs.work');
				</script>
			</div>
		<?php }

	}