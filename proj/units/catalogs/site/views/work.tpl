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
				<script>
					let data = [
						{id: 1, datecr: '10.10.2022 23:45', datemd: '15.10.2022 23:45'},
						{id: 2, datecr: '10.10.2022 23:45', datemd: '16.10.2022 23:45'},
						{id: 3, datecr: '11.10.2022 23:45', datemd: '12.10.2022 23:45'},
						{id: 4, datecr: '11.10.2022 23:45', datemd: '11.10.2022 23:45'},
					];
					let Estimate = new Site.Catalogs.Controller('.view.catalogs.work', data);
				</script>
			</div>
		<?php }

	}